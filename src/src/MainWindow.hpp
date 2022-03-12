#include <iostream>
#include <vector>
#include "NetworkInteraction.hpp"
#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

class MainWindow
{
private:
    tgui::String LoginName;
    std::vector<MessageStructure> AllMessage;
public:
    MainWindow(tgui::String LoginName);
    ~MainWindow() = default;
};