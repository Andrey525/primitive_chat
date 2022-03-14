#include <ClientStruct.hpp>
#include <Commands.hpp>
#include <MessageStruct.hpp>
#include <iostream>
#include <list>

namespace chat {

class Server {
  private:
    std::list<ClientStruct> OnlineUsers;
    std::list<MessageStruct> AllMessages;
    sf::TcpListener Listener;
    size_t MAX_COUNT_MESSAGES = 1024;
  public:
    Server(/* args */);
    ~Server();

    void accept();
    void sendNicknameNewClient(tgui::String nickname);
    void sendListOfAllMessages(tgui::String nickname);
    void sendListOfOnlineMembers(tgui::String nickname);
    void sendMessageToOnlineUsers(MessageStruct msg);
    MessageStruct receiveMessage();
    
};

} // namespace chat