#include <MessageStruct.hpp>
#include <NetworkInteraction.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>

#pragma once

namespace chat {

class ChatRoom {
  private:
    sf::RenderWindow Window;
    tgui::Gui Gui;
    tgui::Theme WidgetsTheme;
    tgui::Picture::Ptr BackgroundPicture;
    tgui::ChatBox::Ptr ChatBox;
    tgui::EditBox::Ptr MessageInputBox;
    tgui::ListBox::Ptr NicknameListBox;
    tgui::Button::Ptr SendMessageButton;
    tgui::String ClientNickname;

  public:
    ChatRoom(tgui::String clientNickname);
    void chatRoomLoop();
    void sendMessage();
};

} // namespace chat