#include <NetworkInteraction.hpp>

namespace chat {

sf::TcpSocket NetworkInteraction::Socket; // init Socket (because static)

bool NetworkInteraction::connectToServer(tgui::String clientNickname) {
    sf::Packet packet;
    bool goodConnection = false;
    if (Socket.connect(sf::IpAddress::LocalHost, 8080) != sf::Socket::Done) {
        return false;
    }
    packet << static_cast<std::string>(clientNickname);
    if (Socket.send(packet) != sf::Socket::Done) {
        exit(-2);
    }
    packet.clear();
    if (Socket.receive(packet) != sf::Socket::Done) {
        exit(-2);
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
    if (Socket.receive(packet) != sf::Socket::Done) {
        exit(-2);
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
        exit(-2);
    }
}

std::list<tgui::String> NetworkInteraction::getListOfOnlineMembers() {
    std::list<tgui::String> nicknames;
    sf::Packet packet;
    uint32_t countMembers;
    std::string nickname;
    if (Socket.receive(packet) != sf::Socket::Done) {
        exit(-2);
    }

    packet >> countMembers;
    for (uint32_t i = 0; i < countMembers; i++) {
        packet >> nickname;
        nicknames.push_back(static_cast<tgui::String>(nickname));
    }
    return nicknames;
}

std::pair<int, tgui::String>
NetworkInteraction::processReceivedNetworkTraffic() {
    sf::Packet packet;
    int operation;
    sf::Socket::Status status;
    status = NetworkInteraction::Socket.receive(packet);
    if (status == sf::Socket::Done) {
        packet >> operation;
        if (operation == NEW_CLIENT) {
            std::string nicknameNewClient;
            packet >> nicknameNewClient;
            return std::make_pair(operation, nicknameNewClient);
        } else if (operation == REMOVE_CLIENT) {
            std::string nicknameRemovedClient;
            packet >> nicknameRemovedClient;
            return std::make_pair(operation, nicknameRemovedClient);

        } else if (operation == NEW_MSG) {
            std::string newMessage;
            std::string nickname;
            tgui::String mergedLine;
            packet >> nickname >> newMessage;
            mergedLine = static_cast<tgui::String>(nickname) + ": " +
                         static_cast<tgui::String>(newMessage);
            return std::make_pair(operation, mergedLine);
        } else if (operation == HELLO) {
            return std::make_pair(operation, "Hello packet");
        }
    } else if (status == sf::Socket::Disconnected) {
        return std::make_pair(DISCONNECT,
                              static_cast<tgui::String>("Disconnect"));
    }
    return std::make_pair(-1, static_cast<tgui::String>("Error"));
}

} // namespace chat
