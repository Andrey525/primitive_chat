#include <ClientStruct.hpp>
#include <Commands.hpp>
#include <MessageStruct.hpp>
#include <iostream>
#include <list>
#include <thread>

namespace chat {

class Server {
  private:
    std::list<ClientStruct> OnlineUsers;
    std::list<MessageStruct> AllMessages;
    size_t MAX_COUNT_MESSAGES = 1024;
    sf::TcpListener Listener;
    sf::Mutex Mutex;

    void sendNicknameNewClientToOther(tgui::String whatNickname);
    void sendListOfAllMessages(tgui::String nicknameToWhom);
    void sendListOfOnlineMembers(tgui::String nicknameToWhom);
    void sendMessageToOnlineUsers(MessageStruct msg);
    void handleNewMessage(MessageStruct msg);
    void sendWhichUserHasRetired(tgui::String user);
    const std::list<ClientStruct>::iterator
    findUserInList(tgui::String nickname);

  public:
    Server();
    ~Server();
    void checkDisconectedUsers();
    void accept();
    void requestHandler();
    void closeServer();
};

} // namespace chat