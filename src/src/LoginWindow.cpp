#include "LoginWindow.hpp"
#include "NetworkInteraction.hpp"

namespace chat {

LoginWindow::LoginWindow() {
    Window.create(sf::VideoMode(400, 300), "Login",
                  sf::Style::Titlebar | sf::Style::Close);
    Window.setFramerateLimit(60);
    Window.setKeyRepeatEnabled(false);

    Gui.setWindow(Window);
    // Gui.setFont(static_cast<tgui::Font>(PathToFont));

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
    ConfirmButton->onClick(&LoginWindow::CheckLoginName, this);
    Gui.add(ConfirmButton);

    NicknameInputBox->onMouseEnter(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Text); });
    NicknameInputBox->onMouseLeave(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow); });

    ConfirmButton->onMouseEnter(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Hand); });
    ConfirmButton->onClick([&]() {
        Label->setText("Nickname is taken...\nTry enter another nickname");
        Label->getRenderer()->setTextColor(tgui::Color(255, 206, 26));
        NicknameInputBox->setText("");
    });
    ConfirmButton->onMouseLeave(
        [&]() { Gui.setOverrideMouseCursor(tgui::Cursor::Type::Arrow); });
}

void LoginWindow::renderWindow() {
    while (Window.isOpen()) {
        sf::Event event;
        while (Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Window.close();
            }
            // if (event.type == sf::Event::KeyPressed) {
            //     if (event.key.code == sf::Keyboard::Enter) {
            //         ConfirmButton->onClick([&]() {
            //             Label->setText(
            //                 "Nickname is taken...\nTry enter another
            //                 nickname");
            //             Label->getRenderer()->setTextColor(
            //                 tgui::Color(255, 206, 26));
            //             NicknameInputBox->setText("");
            //         });
            //     }
            // }
            Gui.handleEvent(event);
        }
        Window.clear();
        Gui.draw();
        Window.display();
    }
}

void LoginWindow::CheckLoginName()
{
    AllLoginName = NetworkInteraction::GetAllLoginName();
    if (NicknameInputBox->getText().length() < 10)
    {
        for(auto item : AllLoginName)
        {
            if (NicknameInputBox->getText() == item)
            {
                GoodAvtorization = false;                    
                break;
            }
        }
        LoginName = NicknameInputBox->getText();
        GoodAvtorization = true;        
    }
    GoodAvtorization = false;
}

} // namespace chat