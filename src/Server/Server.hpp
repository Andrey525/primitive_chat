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

  public:
    Server(/* args */);
    ~Server();

    void accept();
    void sendNicknameNewClient();
    void sendListOfAllMessages();
    void sendListOfOnlineMembers();
    void receiveMessage();
    void sendMessageToOnlineUsers();
};

} // namespace chat