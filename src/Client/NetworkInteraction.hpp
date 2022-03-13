#pragma once
#include "MessageStructure.hpp"
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>
#include <SFML/Network.hpp>

class NetworkInteraction {
  private:
    NetworkInteraction() = default;
    ~NetworkInteraction() = default;
    
    sf::IpAddress ServerIpAdress;
    ushort ServerPort;

  public:
    std::vector<MessageStructure> static Update();
    std::vector<tgui::String> static GetAllLoginName();
    void static SendMSG(tgui::String msg, tgui::String LoginName);
};