#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <string>

#pragma once

namespace chat {

class LoginWindow {
  private:
    tgui::String LoginName;
    sf::RenderWindow Window;
    tgui::Gui Gui;
    tgui::Theme WidgetsTheme;
    tgui::Picture::Ptr BackgroundPicture;
    tgui::Label::Ptr Label;
    tgui::EditBox::Ptr NicknameInputBox;
    tgui::Button::Ptr ConfirmButton;
    // std::string PathToFont{"./font/Revamped.otf"};
    std::vector<std::string> AllLoginName;
    bool GoodAvtorization = NULL;
    int MAX_SIZE_LENGHT_NAME = 14;
  public:
    LoginWindow();
    void renderWindow();
    void CheckLoginName();

    void set_LoginName(tgui::String LoginName) { this->LoginName = LoginName;}
    tgui::String get_LoginName() { return LoginName; }
};

} // namespace chat
