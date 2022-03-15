#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>

namespace chat {

struct ClientStruct {
    sf::TcpSocket Socket;
    tgui::String Nickname;
    bool Isconected = true;
};

} // namespace chat