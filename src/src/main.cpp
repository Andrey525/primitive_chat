#include <SFML/Graphics.hpp>

int main() {
    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile("./img/login.png");
    sprite.setTexture(texture);
    sf::RenderWindow windowLogin(sf::VideoMode(400, 200), "Login",
                                 sf::Style::Titlebar | sf::Style::Close);
    windowLogin.setFramerateLimit(60);

    while (windowLogin.isOpen()) {
        sf::Event event;
        while (windowLogin.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                windowLogin.close();
            }
        }

        windowLogin.clear(sf::Color::Black);
        windowLogin.draw(sprite);
        windowLogin.display();
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Chat",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(0, 0));
    window.setMouseCursorVisible(true);
    window.setMouseCursorGrabbed(false);
    window.setFramerateLimit(60);

    texture.loadFromFile("./img/chat.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));

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
    return 0;
}