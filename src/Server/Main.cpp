#include <Server.hpp>
#include <iostream>
#include <termios.h>
#include <unistd.h>

bool checkExit(chat::Server &server)
{
    struct termios oldt, newt;
    char ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    if(ch == 'q')
    {
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
    std::cout << "Нажми на 'q' что бы остановить сервер" << std::endl;
    while (1) {
        server.checkDisconectedUsers();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if(checkExit(server))
            break; 
    }
    thread.terminate();
    threadForMessage.terminate();
    server.closeServer();
    system("sudo kill -9 8080");
    return 0;
}