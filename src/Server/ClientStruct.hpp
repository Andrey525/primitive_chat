#pragma once

#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>

namespace chat {

struct ClientStruct {
    sf::TcpSocket Socket;
    tgui::String Nickname;
};

} // namespace chat