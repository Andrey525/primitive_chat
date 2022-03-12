#include "MainWindow.hpp"
#include <NetworkInteraction.hpp>

MainWindow::MainWindow(tgui::String LoginName)
{
    this->LoginName = LoginName;
    AllMessage = NetworkInteraction::Update();
    //ВРЕМЯ РИСОВАТЬ БЭК
}