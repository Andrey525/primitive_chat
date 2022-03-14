#include <NetworkInteraction.hpp>

namespace chat {

sf::TcpSocket NetworkInteraction::Socket; // init Socket (because static)

void NetworkInteraction::connectToServer(tgui::String clientNickname) {
    sf::Packet packet;
    // // if (Socket.connect("Server IP-address", port) != sf::Socket::Done) {
    // //     // error
    // // }
    packet << NEW_CONNECTION << static_cast<std::string>(clientNickname);
    // if (Socket.send(packet) != sf::Socket::Done) {
    //     // error
    // }
}

std::list<MessageStruct> NetworkInteraction::getListOfAllMessages() {
    std::list<MessageStruct> result;
    return result;
}

void NetworkInteraction::sendMSG(tgui::String msg, tgui::String nickname) {
    sf::Packet packet;
    packet << NEW_MSG << static_cast<std::string>(nickname)
           << static_cast<std::string>(msg);
    // if (Socket.send(packet) != sf::Socket::Done) {
    //     // error
    // }
}
std::list<tgui::String> NetworkInteraction::getListOfOnlineMembers() {
    sf::Packet packet;
    std::list<tgui::String> nicknames;

    packet << REQUEST_NICKNAMES_LIST;
    // if (Socket.send(packet) != sf::Socket::Done) {
    //     // error
    // }
    // if (Socket.receive(nicknames, sizeof(std::list<tgui::String>) * (size
    // вектора, но он неизвестен!)) != sf::Socket::Done) {
    //     // error
    // }

    return nicknames;
}

} // namespace chat
