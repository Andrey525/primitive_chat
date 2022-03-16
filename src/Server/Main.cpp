#include <Server.hpp>
#include <iostream>

int main() {
    chat::Server server;
    // sf::Thread thread(&chat::Server::accept, &server);
    // thread.launch();
    while (1) {
        server.accept();
        server.checkDisconectedUsers();
    }

    return 0;
}