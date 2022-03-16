#include <Server.hpp>
#include <iostream>

int main() {
    chat::Server server;
    sf::Thread thread(&chat::Server::accept, &server);
    sf::Thread threadForMessage(&chat::Server::requestHandler, &server);
    thread.launch();
    threadForMessage.launch();
    while (1) {
        server.checkDisconectedUsers();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}