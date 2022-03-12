#include "ClientWindow.hpp"
#include "LoginWindow.hpp"
#include "NetworkInteraction.hpp"

int main() {
    // chat::LoginWindow loginWindow;
    // loginWindow.renderWindow();
    chat::ClientWindow clientWindow("Dima");
    clientWindow.renderWindow();
    return 0;
}