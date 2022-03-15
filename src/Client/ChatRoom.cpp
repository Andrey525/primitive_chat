#include <ChatRoom.hpp>
#include <NetworkInteraction.hpp>

namespace chat {

ChatRoom::ChatRoom(tgui::String clientNickname) {

    setupWindow();
    setupEventHandlers();

    ClientNickname = clientNickname;
    NicknameListBox->addItem(ClientNickname);

    // std::list<tgui::String> membersOnlineNicknames =
    //     NetworkInteraction::getListOfOnlineMembers();
    // for (auto otherMemberNickname : membersOnlineNicknames) {
    //     NicknameListBox->addItem(otherMemberNickname);
    // }

    // std::list<MessageStruct> listOfAllMessages =
    //     NetworkInteraction::getListOfAllMessages();
    // for (auto messageStruct : listOfAllMessages) {
    //     ChatBox->addLine(messageStruct.Nickname + ": " +
    //     messageStruct.Message);
    // }
}

void ChatRoom::setupWindow() {
    Window.create(sf::VideoMode(800, 600), "Chat-Client",
                  sf::Style::Titlebar | sf::Style::Close);
    Window.setFramerateLimit(60);
    Window.setKeyRepeatEnabled(false);

    Gui.setWindow(Window);

    WidgetsTheme.load("./themes/Black.txt");

    BackgroundPicture = tgui::Picture::create("./img/clientBackground.jpg");
    BackgroundPicture->setSize({"100%", "100%"});
    Gui.add(BackgroundPicture);

    ChatBox = tgui::ChatBox::create();
    ChatBox->setRenderer(WidgetsTheme.getRenderer("ChatBox"));
    ChatBox->setSize(525, 475);
    ChatBox->setPosition(25, 25);
    ChatBox->setTextSize(20);
    ChatBox->setTextColor(tgui::Color(200, 200, 200));
    ChatBox->setLinesStartFromTop();
    Gui.add(ChatBox);

    MessageInputBox = tgui::EditBox::create();
    MessageInputBox->setRenderer(WidgetsTheme.getRenderer("EditBox"));
    MessageInputBox->setSize(525, 50);
    MessageInputBox->setPosition(25, 525);
    MessageInputBox->setTextSize(20);
    MessageInputBox->setDefaultText("Enter message...");
    Gui.add(MessageInputBox);

    NicknameListBox = tgui::ListBox::create();
    NicknameListBox->setRenderer(WidgetsTheme.getRenderer("ListBox"));
    NicknameListBox->setSize(200, 475);
    NicknameListBox->setPosition(575, 25);
    NicknameListBox->setTextSize(20);
    Gui.add(NicknameListBox);

    SendMessageButton = tgui::Button::create();
    SendMessageButton->setRenderer(WidgetsTheme.getRenderer("Button"));
    SendMessageButton->setSize(200, 50);
    SendMessageButton->setPosition(575, 525);
    SendMessageButton->setText("Send");
    SendMessageButton->setTextSize(20);
    Gui.add(SendMessageButton);
}

void ChatRoom::setupEventHandlers() {
    MessageInputBox->onMouseEnter(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Text); });
    MessageInputBox->onMouseLeave(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow); });

    SendMessageButton->onMouseEnter(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Hand); });
    SendMessageButton->onClick(&ChatRoom::sendMessage, this);
    SendMessageButton->onMouseLeave(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow); });
}

void ChatRoom::chatRoomLoop() {
    while (Window.isOpen()) {
        sf::Event event;
        while (Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Window.close();
            }
            Gui.handleEvent(event);
        }
        Window.clear();
        Gui.draw();
        Window.display();
    }
}

void ChatRoom::sendMessage() {
    if (MessageInputBox->getText().length() > 0) {
        tgui::String temp;
        temp = MessageInputBox->getText();
        ChatBox->addLine(ClientNickname + ": " + temp);
        MessageInputBox->setText("");
        NetworkInteraction::sendMSG(temp, ClientNickname);
    }
}

} // namespace chat