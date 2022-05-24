#include <Client/Login.hpp>

namespace chat {

Login::Login() {
    setupWindow();
    setupEventHandlers();
}

void Login::setupWindow() {
    Window.create(sf::VideoMode(400, 300), "Login",
                  sf::Style::Titlebar | sf::Style::Close);
    Window.setFramerateLimit(60);

    Gui.setWindow(Window);

    WidgetsTheme.load("./themes/Black.txt");

    BackgroundPicture = tgui::Picture::create("./img/loginBackground.png");
    Gui.add(BackgroundPicture);

    Label = tgui::Label::create();
    Label->setRenderer(WidgetsTheme.getRenderer("Label"));
    Label->setText("Log in\nto join the chat:");
    Label->setSize(300, 50);
    Label->setPosition(50, 40);
    Label->setTextSize(20);
    Label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    Gui.add(Label);

    NicknameInputBox = tgui::EditBox::create();
    NicknameInputBox->setRenderer(WidgetsTheme.getRenderer("EditBox"));
    NicknameInputBox->setSize(200, 50);
    NicknameInputBox->setTextSize(20);
    NicknameInputBox->setPosition(100, 115);
    NicknameInputBox->setDefaultText("Your nick...");
    Gui.add(NicknameInputBox);

    ConfirmButton = tgui::Button::create();
    ConfirmButton->setRenderer(WidgetsTheme.getRenderer("Button"));
    ConfirmButton->setText("Confirm");
    ConfirmButton->setSize(200, 50);
    ConfirmButton->setTextSize(20);
    ConfirmButton->setPosition(100, 190);
    Gui.add(ConfirmButton);
}

void Login::setupEventHandlers() {
    NicknameInputBox->onMouseEnter(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Text); });
    NicknameInputBox->onMouseLeave(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow); });

    ConfirmButton->onMouseEnter(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Hand); });
    ConfirmButton->onClick(&Login::checkClientNickname, this);
    ConfirmButton->onMouseLeave(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow); });
}

tgui::String Login::loginLoop() {
    while (Window.isOpen()) {
        sf::Event event;
        while (Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Window.close();
            } else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Enter) {
                    checkClientNickname();
                }
            }
            Gui.handleEvent(event);
        }
        Window.clear();
        Gui.draw();
        Window.display();
        if (GoodAvtorization == true) {
            Window.close();
        }
    }
    return ClientNickname;
}

void Login::checkClientNickname() {
    if (NicknameInputBox->getText().length() == 0 ||
        NicknameInputBox->getText().length() > MAX_SIZE_LENGHT_NAME) {
        Label->setText("Nickname's length must be between 1 and 10 chars...");
        NicknameInputBox->setText("");
        return;
    }
    std::pair<bool, int> statusConnection;
    statusConnection =
        NetworkInteraction::connectToServer(NicknameInputBox->getText());
    GoodAvtorization = statusConnection.first;
    if (GoodAvtorization == true) {
        ClientNickname = NicknameInputBox->getText();
        return;
    } else {
        if (statusConnection.second == 0) {
            Label->setText("Nickname is taken...");
            NicknameInputBox->setText("");
        } else {
            Label->setText("Can't connect to the Server...");
            NicknameInputBox->setText("");
        }
        return;
    }
}

} // namespace chat