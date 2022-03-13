#include "NetworkInteraction.hpp"
#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

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
    std::vector<tgui::String> AllLoginName;
    bool GoodAvtorization = false;
    size_t MAX_SIZE_LENGHT_NAME = 10;

  public:
    LoginWindow();
    void renderWindow();
    void checkLoginName();

    void set_LoginName(tgui::String LoginName) { this->LoginName = LoginName; }
    tgui::String get_LoginName() { return LoginName; }
};

} // namespace chat
