#include <Commands.hpp>
#include <MessageStruct.hpp>
#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <list>

#pragma once

namespace chat {

class NetworkInteraction {
  private:
    NetworkInteraction() = default;
    ~NetworkInteraction() = default;

  public:
    static sf::TcpSocket Socket;

    bool static connectToServer(tgui::String clientNickname);
    std::list<MessageStruct> static getListOfAllMessages();
    std::list<tgui::String> static getListOfOnlineMembers();
    void static sendMSG(tgui::String msg, tgui::String clientNickname);
    MessageStruct static recvMSG();
    tgui::String static getNewClient();
};

} // namespace chat