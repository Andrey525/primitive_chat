#include <SFML/Graphics.hpp>
#include <Server.hpp>
#include <iostream>

bool checkExit(chat::Server &server) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        server.closeServer();
        return true;
    }
    return false;
}

int main() {
    chat::Server server;
    sf::Thread thread(&chat::Server::accept, &server);
    sf::Thread threadForMessage(&chat::Server::requestHandler, &server);
    thread.launch();
    threadForMessage.launch();
    std::cout << "Нажмите Escape, чтобы остановить сервер" << std::endl;
    while (1) {
        server.checkDisconectedUsers();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if (checkExit(server))
            break;
    }
    thread.terminate();
    threadForMessage.terminate();
    server.closeServer();
    return 0;
}