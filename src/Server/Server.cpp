#include <Server.hpp>

namespace chat {

Server::Server(/* args */) {
    if (Listener.listen(8080, sf::IpAddress::LocalHost) != sf::Socket::Done) {
        // error
    }
}

Server::~Server() {}

void Server::accept() {
    sf::Packet packet;
    std::string nickname;
    int command;

    OnlineUsers.emplace_back();
    ClientStruct &client = OnlineUsers.back();

    if (Listener.accept(client.Socket) != sf::Socket::Done) {
        // error
    }
    if (client.Socket.receive(packet) != sf::Socket::Done) {
        // error
    }
    packet >> command;
    if (command != NEW_CONNECTION) {
        // error
    }
    packet >> nickname;
    client.Nickname = static_cast<tgui::String>(nickname);
    //надо разослать остальным клиентам никнейм этого
    void sendNicknameNewClient();
    // а этому нужно отправить 2 списка
    // void sendListOfAllMessages();
    // void sendListOfOnlineMembers();
}

void Server::sendListOfAllMessages() {}

void Server::sendListOfOnlineMembers() {}

} // namespace chat