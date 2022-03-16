#include <Server.hpp>

namespace chat {

Server::Server() {
    if (Listener.listen(8080, sf::IpAddress::LocalHost) != sf::Socket::Done) {
        std::cout << "Server Error: listen\n";
    }
}

Server::~Server() {}

void Server::accept() {
    while (true) {
        sf::Packet packet;
        std::string nickname;
        tgui::String tguiNickname;

        OnlineUsers.emplace_back();
        ClientStruct &client = OnlineUsers.back();

        if (Listener.accept(client.Socket) != sf::Socket::Done) {
            std::cout << "Server Error: accpet\n";
        }
        if (client.Socket.receive(packet) != sf::Socket::Done) {
            std::cout << "Server Error: accpet recv\n";
        }
        packet >> nickname;
        tguiNickname = static_cast<tgui::String>(nickname);

        const auto &itClient =
            std::find_if(OnlineUsers.begin(), OnlineUsers.end(),
                         [&](const ClientStruct &st1) -> bool {
                             if (tguiNickname == st1.Nickname) {
                                 return true;
                             }
                             return false;
                         });
        packet.clear();
        if (itClient != OnlineUsers.end()) { // не уникальное имя
            std::cout << "Not unique name\n";
            packet << false;
            if (client.Socket.send(packet) != sf::Socket::Done) {
                std::cout << "Server Error: send AllMessages\n";
            }
            OnlineUsers.pop_back();
            continue;
        } else { // уникальное имя
            std::cout << "Unique name\n";
            packet << true;
            if (client.Socket.send(packet) != sf::Socket::Done) {
                std::cout << "Server Error: send AllMessages\n";
            }
            client.Nickname = tguiNickname;
            sendNicknameNewClientToOther(client.Nickname);
            sendListOfOnlineMembers(client.Nickname);
            sendListOfAllMessages(client.Nickname);
        }
    }
}

void Server::sendListOfAllMessages(tgui::String nicknameToWhom) {
    sf::Packet packet;
    const auto &itClient =
        std::find_if(OnlineUsers.begin(), OnlineUsers.end(),
                     [&](const ClientStruct &st1) -> bool {
                         if (nicknameToWhom == st1.Nickname) {
                             return true;
                         }
                         return false;
                     });

    packet << static_cast<uint32_t>(AllMessages.size());

    std::for_each(AllMessages.begin(), AllMessages.end(),
                  [&packet](const MessageStruct &messageStruct) {
                      packet << static_cast<std::string>(messageStruct.Nickname)
                             << static_cast<std::string>(messageStruct.Message);
                  });

    if (itClient->Socket.send(packet) != sf::Socket::Done) {
        std::cout << "Server Error: send AllMessages\n";
    }
}

void Server::sendListOfOnlineMembers(tgui::String nicknameToWhom) {
    sf::Packet packet;
    const auto &itClient =
        std::find_if(OnlineUsers.begin(), OnlineUsers.end(),
                     [&](const ClientStruct &st1) -> bool {
                         if (nicknameToWhom == st1.Nickname) {
                             return true;
                         }
                         return false;
                     });

    packet << static_cast<uint32_t>(OnlineUsers.size() - 1);

    std::for_each(OnlineUsers.begin(), OnlineUsers.end(),
                  [&packet, &itClient](const ClientStruct &client) {
                      if (itClient->Nickname != client.Nickname) {
                          packet << static_cast<std::string>(client.Nickname);
                      }
                  });

    if (itClient->Socket.send(packet) != sf::Socket::Done) {
        std::cout << "Server Error: send OnlineMembers\n";
    }
}

void Server::sendNicknameNewClientToOther(tgui::String whatNickname) {
    if (OnlineUsers.size() > 1) {
        sf::Packet packet;
        packet << NEW_CLIENT << static_cast<std::string>(whatNickname);
        for (auto &user : OnlineUsers) {
            if (whatNickname == user.Nickname) {
                continue;
            }
            if (user.Socket.send(packet) != sf::Socket::Done) {
                std::cout << "Server Error: send nickname to other\n";
            }
        }
    }
}

void Server::checkDisconectedUsers() {
    sf::Packet packet;
    packet << HELLO;
    auto it_last = OnlineUsers.end();
    it_last--;
    for (auto it = OnlineUsers.begin(); it != it_last;) {
        if (it->Socket.send(packet) == sf::Socket::Disconnected) {
            sendWhichUserHasRetired(it->Nickname);
            it = OnlineUsers.erase(it);
            std::cout << "Element was erased!\n";
        } else {
            it++;
        }
    }
}

void Server::sendWhichUserHasRetired(tgui::String nickname) {
    sf::Packet packet;
    packet << REMOVE_CLIENT << static_cast<std::string>(nickname);
    auto it_last = OnlineUsers.end();
    it_last--;
    for (auto it = OnlineUsers.begin(); it != it_last; it++) {
        if (it->Nickname == nickname) {
            continue;
        }
        if (it->Socket.send(packet) != sf::Socket::Done) {
            std::cout << "Server Error: send nickname to other\n";
        }
    }
}

void Server::sendMessageToOnlineUsers(MessageStruct msg) {
    sf::Packet packet;
    packet << NEW_MSG << static_cast<std::string>(msg.Nickname)
           << static_cast<std::string>(msg.Message);
    for (auto &user : OnlineUsers) {
        if (msg.Nickname == user.Nickname) {
            continue;
        }
        if (user.Socket.send(packet) != sf::Socket::Done) {
            std::cout << "Server Error: send message to online users\n";
        }
    }
}

void Server::handleNewMessage(MessageStruct msg) {
    AllMessages.push_back(msg);
    if (AllMessages.size() == MAX_COUNT_MESSAGES) {
        AllMessages.pop_front();
    }
    sendMessageToOnlineUsers(msg);
}

void Server::requestHandler(sf::Packet &packet) {
    int command;
    packet >> command;
    if (command == NEW_MSG) {
        std::string nickname;
        std::string message;
        packet >> nickname >> message;
        handleNewMessage(MessageStruct(static_cast<tgui::String>(nickname),
                                       static_cast<tgui::String>(message)));
    }
}

} // namespace chat