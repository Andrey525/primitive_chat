#include <NetworkInteraction.hpp>

namespace chat {

sf::TcpSocket NetworkInteraction::Socket; // init Socket (because static)
int NetworkInteraction::MAX_COUNT_USERS = 32;
int NetworkInteraction::MAX_COUNT_MESSAGES = 1024;
void NetworkInteraction::connectToServer(tgui::String clientNickname) {
    sf::Packet packet;
    if (Socket.connect(sf::IpAddress::LocalHost, 8080) != sf::Socket::Done) {
         // error
    }
    packet << NEW_CONNECTION << static_cast<std::string>(clientNickname);
    if (Socket.send(packet) != sf::Socket::Done) {
        // error
    }
}

std::list<MessageStruct> NetworkInteraction::getListOfAllMessages() {
    std::list<MessageStruct> result;
    sf::Packet packet;
    size_t countbytes;
    packet << REQUEST_LAST_MESSAGES;
    if(Socket.send(packet) != sf::Socket::Done)
    {

    }
    Socket.setBlocking(true);
    if(Socket.receive(&result, sizeof(MessageStruct) * MAX_COUNT_MESSAGES,countbytes) != sf::Socket::Done)
    {
        
    }
    return result;
}

void NetworkInteraction::sendMSG(tgui::String msg, tgui::String nickname) {
    sf::Packet packet;
    packet << NEW_MSG << static_cast<std::string>(nickname)
           << static_cast<std::string>(msg);
    if (Socket.send(packet) != sf::Socket::Done) {
        // error
    }
}
std::list<tgui::String> NetworkInteraction::getListOfOnlineMembers() {
    sf::Packet packet;
    std::list<tgui::String> nicknames;
    size_t countbytes = 0;
    packet << REQUEST_NICKNAMES_LIST;
    if (Socket.send(packet) != sf::Socket::Done) {
        // error
    }
    if (Socket.receive(&nicknames, (sizeof(std::list<tgui::String>) * NetworkInteraction::MAX_COUNT_USERS), countbytes) != sf::Socket::Done) {
        // error
    }
    return nicknames;
}

} // namespace chat
