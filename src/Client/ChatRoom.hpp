#include <MessageStruct.hpp>
#include <NetworkInteraction.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <list>

#pragma once

namespace chat {

class ChatRoom {

    friend class NetworkInteraction;

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
    bool IsStart = false;
    bool IsEnd = false;

    void setupWindow();
    void setupEventHandlers();
    void sendMessage();
    void addNewMessage(tgui::String mergedLine);
    void addNewClient(tgui::String nicknameNewClient);
    void removeClient(tgui::String nicknameRemovedClient);
    void startProcessReceivingNetworkTraffic();

  public:
    ChatRoom(tgui::String clientNickname);
    void chatRoomLoop();
};

} // namespace chat