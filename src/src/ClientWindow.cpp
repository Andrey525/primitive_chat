#include <Chat.hpp>
#include <SFML/Graphics.hpp>

namespace chat {

void drawClientWindow() {
    sf::Texture texture;
    sf::Sprite sprite;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Chat",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(0, 0));
    window.setMouseCursorVisible(true);
    window.setMouseCursorGrabbed(false);
    window.setFramerateLimit(60);

    texture.loadFromFile("./img/chat.png");
    sprite.setTexture(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }
}

} // namespace chat