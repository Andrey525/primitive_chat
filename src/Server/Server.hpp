#include <ClientStruct.hpp>
#include <Commands.hpp>
#include <MessageStruct.hpp>
#include <iostream>
#include <list>

namespace chat {

class Server {
  private:
    std::list<ClientStruct> OnlineUsers;
    std::list<MessageStruct> AllMessages{{"Andrey", "Message 1"},
                                         {"Dima", "Message 2"}};
    sf::TcpListener Listener;
    size_t MAX_COUNT_MESSAGES = 1024;

  public:
    // активирует Listener'a
    Server();
    ~Server();

    // проверяет, есть ли имя клиента в списке имен и устанавливает связь с
    // клиентом. если проверки уникальности имени прошли, то добавляем клиента в
    // список участников и вызывает sendNicknameNewClientToOther
    void accept();

    //отправляет имя whatNickname всем остальным клиентам
    void sendNicknameNewClientToOther(tgui::String whatNickname);

    // отправляет список собщений клиенту с именем nicknameToWhom
    void sendListOfAllMessages(tgui::String nicknameToWhom);

    // отправляет список участников клиенту с именем nicknameToWhom
    void sendListOfOnlineMembers(tgui::String nicknameToWhom);

    // рассылает всем, кроме отправителя, данное сообщение
    void sendMessageToOnlineUsers(MessageStruct msg);

    //добавляет сообщение в список и потом вызывает sendMessageToOnlineUsers
    void handleNewMessage(MessageStruct msg);

    //получает пакет, в зависимости от команды правильно распаковывает пакет и
    //вызывает один из верхних методов
    void requestHandler(sf::Packet &packet, tgui::String whoseRequest);

    void checkDisconectedUsers();
    void sendWhichUserHasRetired(tgui::String user);
};

} // namespace chat