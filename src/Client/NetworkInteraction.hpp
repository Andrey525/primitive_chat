#pragma once
#include "MessageStructure.hpp"
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

class NetworkInteraction {
  private:
    NetworkInteraction() = default;
    ~NetworkInteraction() = default;

  public:
    std::vector<MessageStructure> static Update();
    std::vector<tgui::String> static GetAllLoginName();
    void static SendMSG(tgui::String msg, tgui::String LoginName);
};