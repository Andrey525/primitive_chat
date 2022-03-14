#include <Commands.hpp>
#include <MessageStruct.hpp>
#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

#pragma once

class NetworkInteraction {
  private:
    NetworkInteraction() = default;
    ~NetworkInteraction() = default;

  public:
    static sf::TcpSocket Socket;

    void static connectToServer(tgui::String clientNickname);
    std::vector<MessageStruct> static getListOfLastMessages();
    std::vector<tgui::String> static getListOfOnlineMembers();
    void static sendMSG(tgui::String msg, tgui::String clientNickname);
};