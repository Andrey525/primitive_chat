#include <Server.hpp>
#include <iostream>
#include <thread>

int main() {
    chat::Server server;
    sf::Thread thread(&chat::Server::accept, &server);
    sf::Thread threadForMessage(&chat::Server::requestHandler, &server);
    thread.launch();
    threadForMessage.launch();
    while (1) {
        // server.accept();
        server.checkDisconectedUsers();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}