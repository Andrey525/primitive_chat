#include "LoginWindow.hpp"

namespace chat {

void handler() { std::cout << "Button was clicked\n"; }

LoginWindow::LoginWindow() {
    Window.create(sf::VideoMode(400, 300), "Login",
                  sf::Style::Titlebar | sf::Style::Close);
    Window.setFramerateLimit(60);

    Gui.setWindow(Window);
    Gui.setFont(static_cast<tgui::Font>(PathToFont));

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
    // Label->getRenderer()->setTextColor(tgui::Color::Black);
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

void LoginWindow::renderWindow() {
    while (Window.isOpen()) {
        sf::Event event;
        while (Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Window.close();
            }
            Gui.handleEvent(event);
        }
        ConfirmButton->onClick(handler);
        Window.clear();
        Gui.draw();
        Window.display();
    }
}

} // namespace chat