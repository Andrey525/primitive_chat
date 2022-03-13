#include <iostream>
#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>

struct ClientStruct
{
    sf::IpAddress IpAdress;
    ushort port;
    tgui::String LoginName;
};
