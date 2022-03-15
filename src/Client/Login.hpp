#include <MessageStruct.hpp>
#include <NetworkInteraction.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <list>

#pragma once

namespace chat {

class Login {
  private:
    sf::RenderWindow Window;
    tgui::Gui Gui;
    tgui::Theme WidgetsTheme;
    tgui::Picture::Ptr BackgroundPicture;
    tgui::Label::Ptr Label;
    tgui::EditBox::Ptr NicknameInputBox;
    tgui::Button::Ptr ConfirmButton;
    tgui::String ClientNickname;
    bool GoodAvtorization = false;
    size_t MAX_SIZE_LENGHT_NAME = 10;

    void setupWindow();
    void setupEventHandlers();
    void checkClientNickname();

  public:
    Login();
    tgui::String loginLoop();
};

} // namespace chat
