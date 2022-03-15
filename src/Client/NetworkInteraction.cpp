#include <NetworkInteraction.hpp>

namespace chat {

sf::TcpSocket NetworkInteraction::Socket; // init Socket (because static)

tgui::String NetworkInteraction::getNewClient()
{
    sf::Packet packet;
    std::string newNicname;
    if (Socket.receive(packet) != sf::Socket::Done)
    {
        std::cout << "Что то пошло не так в recieve=(" << std::endl;
    }
    packet >> newNicname;
    return static_cast<tgui::String>(newNicname);
}

bool NetworkInteraction::connectToServer(tgui::String clientNickname) {
    sf::Packet packet;
    bool goodConnection = false;
    Socket.setBlocking(true);
    if (Socket.connect(sf::IpAddress::LocalHost, 8080) != sf::Socket::Done) {
        std::cout << "Error connect\n";
    }
    packet << static_cast<std::string>(clientNickname);
    if (Socket.send(packet) != sf::Socket::Done) {
        std::cout << "Error send NEW_CONNECTION \n";
    }
    packet.clear();
    if (Socket.receive(packet) != sf::Socket::Done) {
        std::cout << "Error recv status connection\n";
    }
    packet >> goodConnection;
    if (goodConnection == false) {
        Socket.disconnect();
    }
    return goodConnection;
}

std::list<MessageStruct> NetworkInteraction::getListOfAllMessages() {
    std::list<MessageStruct> messages;
    sf::Packet packet;
    uint32_t countAllMessages;
    std::string nickname;
    std::string message;
    packet << REQUEST_LAST_MESSAGES;
    if (Socket.send(packet) != sf::Socket::Done) {
        std::cout << "Error send REQUEST_LAST_MESSAGES\n";
    }
    if (Socket.receive(packet) != sf::Socket::Done) {
        std::cout << "Error receive LAST_MESSAGES\n";
    }

    packet >> countAllMessages;
    for (uint32_t i = 0; i < countAllMessages; i++) {
        packet >> nickname >> message;
        messages.emplace_back(static_cast<tgui::String>(nickname),
                              static_cast<tgui::String>(message));
    }
    return messages;
}

void NetworkInteraction::sendMSG(tgui::String msg, tgui::String nickname) {
    sf::Packet packet;
    packet << NEW_MSG << static_cast<std::string>(nickname)
           << static_cast<std::string>(msg);
    if (Socket.send(packet) != sf::Socket::Done) {
        std::cout << "Error send NEW_MSG\n";
    }
}

MessageStruct NetworkInteraction::recvMSG() {
    MessageStruct recvMessage;
    return recvMessage;
}

std::list<tgui::String> NetworkInteraction::getListOfOnlineMembers() {
    std::list<tgui::String> nicknames;
    sf::Packet packet;
    uint32_t countMembers;
    std::string nickname;
    packet << REQUEST_NICKNAMES_LIST;
    if (Socket.send(packet) != sf::Socket::Done) {
        std::cout << "Error send REQUEST_NICKNAMES_LIST\n";
    }
    if (Socket.receive(packet) != sf::Socket::Done) {
        std::cout << "Error receive NICKNAMES_LIST\n";
    }

    packet >> countMembers;
    for (uint32_t i = 0; i < countMembers; i++) {
        packet >> nickname;
        nicknames.push_back(static_cast<tgui::String>(nickname));
    }
    return nicknames;
}

} // namespace chat
