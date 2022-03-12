#include "MainWindow.hpp"
#include <NetworkInteraction.hpp>

MainWindow::MainWindow(std::string LoginName)
{
    this->LoginName = LoginName;
    AllMessage = NetworkInteraction::Update();
    //ВРЕМЯ РИСОВАТЬ БЭК
}