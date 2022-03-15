#include <Server.hpp>
#include <iostream>

int main() {
    chat::Server server;
    while (1) {
        server.accept();
    }

    return 0;
}