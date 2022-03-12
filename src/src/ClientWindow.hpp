#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

#pragma once

namespace chat {

class ClientWindow {
  private:
    sf::RenderWindow Window;
    tgui::Gui Gui;
    tgui::Theme WidgetsTheme;
    tgui::Picture::Ptr BackgroundPicture;
    tgui::ChatBox::Ptr ChatBox;
    tgui::EditBox::Ptr MessageInputBox;
    tgui::ListBox::Ptr NicknameListBox;
    tgui::Button::Ptr SendMessageButton;

  public:
    ClientWindow();
    void renderWindow();
};

} // namespace chat