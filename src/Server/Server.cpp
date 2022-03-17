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
    sf::Socket::Status status;
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
    Mutex.lock();
    status = itClient->Socket.send(packet);
    Mutex.unlock();
    if (status != sf::Socket::Done) {
        std::cout << "Server Error: send AllMessages\n";
    }
}

void Server::sendListOfOnlineMembers(tgui::String nicknameToWhom) {
    sf::Packet packet;
    sf::Socket::Status status;
    const auto &itClient =
        std::find_if(OnlineUsers.begin(), OnlineUsers.end(),
                     [&](const ClientStruct &st1) -> bool {
                         if (nicknameToWhom == st1.Nickname) {
                             return true;
                         }
                         return false;
                     });

    packet << static_cast<uint32_t>(OnlineUsers.size() - 1);
    auto it_last = OnlineUsers.end();
    it_last--;
    std::for_each(OnlineUsers.begin(), it_last,
                  [&packet, &itClient](const ClientStruct &client) {
                      if (itClient->Nickname != client.Nickname) {
                          packet << static_cast<std::string>(client.Nickname);
                      }
                  });
    Mutex.lock();
    status = itClient->Socket.send(packet);
    Mutex.unlock();
    if (status != sf::Socket::Done) {
        std::cout << "Server Error: send OnlineMembers\n";
    }
}

void Server::sendNicknameNewClientToOther(tgui::String whatNickname) {
    if (OnlineUsers.size() > 1) {
        sf::Packet packet;
        sf::Socket::Status status;
        packet << NEW_CLIENT << static_cast<std::string>(whatNickname);
        auto it_last = OnlineUsers.end();
        it_last--;
        for (auto it = OnlineUsers.begin(); it != it_last; it++) {
            if (whatNickname == it->Nickname) {
                continue;
            }
            Mutex.lock();
            status = it->Socket.send(packet);
            Mutex.unlock();
            if (status != sf::Socket::Done) {
                std::cout << "Server Error: send nickname to other\n";
            }
        }
    }
}

void Server::checkDisconectedUsers() {
    sf::Packet packet;
    sf::Socket::Status status;
    packet << HELLO;
    auto it_last = OnlineUsers.end();
    it_last--;
    for (auto it = OnlineUsers.begin(); it != it_last;) {
        Mutex.lock();
        status = it->Socket.send(packet);
        Mutex.unlock();
        if (status == sf::Socket::Disconnected) {
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
    sf::Socket::Status status;
    packet << REMOVE_CLIENT << static_cast<std::string>(nickname);
    auto it_last = OnlineUsers.end();
    it_last--;
    for (auto it = OnlineUsers.begin(); it != it_last; it++) {
        if (it->Nickname == nickname) {
            continue;
        }
        Mutex.lock();
        status = it->Socket.send(packet);
        Mutex.unlock();
        if (status != sf::Socket::Done) {
            std::cout << "Server Error: send nickname to other\n";
        }
    }
}

void Server::sendMessageToOnlineUsers(MessageStruct msg) {
    sf::Packet packet;
    sf::Socket::Status status;
    packet << NEW_MSG << static_cast<std::string>(msg.Nickname)
           << static_cast<std::string>(msg.Message);
    auto it_last = OnlineUsers.end();
    it_last--;
    for (auto it = OnlineUsers.begin(); it != it_last; it++) {
        if (msg.Nickname == it->Nickname) {
            continue;
        }
        Mutex.lock();
        status = it->Socket.send(packet);
        Mutex.unlock();
        if (status != sf::Socket::Done) {
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

void Server::requestHandler() {
    while (true) {
        sf::Packet packet;
        sf::Socket::Status status;
        auto it_last = OnlineUsers.end();
        it_last--;
        std::string nickname;
        std::string newMessage;
        for (auto it = OnlineUsers.begin(); it != it_last; it++) {
            Mutex.lock();
            it->Socket.setBlocking(false);
            status = it->Socket.receive(packet);
            it->Socket.setBlocking(true);
            Mutex.unlock();
            if (status == sf::Socket::Done) {
                int command;
                packet >> command;
                if (command == NEW_MSG) {
                    std::string nickname;
                    std::string message;
                    packet >> nickname >> message;
                    handleNewMessage(
                        MessageStruct(static_cast<tgui::String>(nickname),
                                      static_cast<tgui::String>(message)));
                }
            } else if (status == sf::Socket::NotReady) {

            } else if (status == sf::Socket::Disconnected) {

            } else if (status == sf::Socket::Error) {
                std::cout << "Error, can't get packet!\n";
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

} // namespace chat