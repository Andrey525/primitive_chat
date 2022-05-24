#include <Client/ChatRoom.hpp>
#include <Client/Login.hpp>
#include <Client/NetworkInteraction.hpp>

int main() {
    chat::Login login;
    tgui::String clientNickname = login.loginLoop();
    // if window was closed
    if (static_cast<std::string>(clientNickname).empty()) {
        return 0;
    }
    chat::ChatRoom chatRoom(clientNickname);
    chatRoom.chatRoomLoop();
    return 0;
}