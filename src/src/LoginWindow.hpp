#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <string>

#pragma once

namespace chat {

class LoginWindow {
  private:
    std::string LoginName;
    sf::RenderWindow Window;
    tgui::Gui Gui;
    tgui::Theme WidgetsTheme;
    tgui::Picture::Ptr BackgroundPicture;
    tgui::Label::Ptr Label;
    tgui::EditBox::Ptr NicknameInputBox;
    tgui::Button::Ptr ConfirmButton;
    // std::string PathToFont{"./font/Revamped.otf"};

  public:
    LoginWindow();
    void renderWindow();

    void set_LoginName(std::string LoginName) { this->LoginName = LoginName;}

    std::string get_LoginName() { return LoginName; }


};

} // namespace chat
