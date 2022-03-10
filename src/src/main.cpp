// #include <Chat.hpp>

// int main() {
//     chat::drawLoginWindow();
//     chat::drawClientWindow();
//     return 0;
// }

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window{sf::VideoMode(800, 600), "TGUI example"};
    tgui::Theme theme{"./themes/Black.txt"};
    tgui::Gui gui(window);

    auto editBox = tgui::EditBox::create();
    editBox->setRenderer(theme.getRenderer("EditBox"));
    editBox->setSize(200, 25);
    editBox->setTextSize(18);
    editBox->setPosition(10, 270);
    editBox->setDefaultText("Click to edit text...");
    gui.add(editBox);

    auto listBox = tgui::ListBox::create();
    listBox->setRenderer(theme.getRenderer("ListBox"));
    listBox->setSize(250, 120);
    listBox->setItemHeight(24);
    listBox->setPosition(10, 340);
    listBox->addItem("Item 1");
    listBox->addItem("Item 2");
    listBox->addItem("Item 3");
    gui.add(listBox);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event);
        }
        window.clear();
        gui.draw();
        window.display();
    }
    return 0;
}