#include <Server.hpp>

namespace chat
{

    Server::Server(/* args */)
    {
        if (Listener.listen(8080, sf::IpAddress::LocalHost) != sf::Socket::Done)
        {
            // error
        }
    }

    Server::~Server() {}

    void Server::accept()
    {
        sf::Packet packet;
        std::string nickname;
        int command;

        OnlineUsers.emplace_back();
        ClientStruct &client = OnlineUsers.back();

        if (Listener.accept(client.Socket) != sf::Socket::Done)
        {
            // error
        }
        if (client.Socket.receive(packet) != sf::Socket::Done)
        {
            // error
        }
        packet >> command;
        if (command != NEW_CONNECTION)
        {
            // error
        }
        packet >> nickname;
        client.Nickname = static_cast<tgui::String>(nickname);
        //надо разослать остальным клиентам никнейм этого
        void sendNicknameNewClient();
        // а этому нужно отправить 2 списка
        sendListOfOnlineMembers(client.Nickname);
        sendListOfAllMessages(client.Nickname);
    }

    void Server::sendListOfAllMessages(tgui::String nickname)
    {
        auto itClient = std::find_if(OnlineUsers.begin(), OnlineUsers.end(), [&](const ClientStruct &st1)->bool{
        if (nickname == st1.Nickname)
        {
            return true;
        }
        return false; });
        if (itClient->Socket.send(&AllMessages, sizeof(MessageStruct)* AllMessages.size()) != sf::Socket::Done ) 
        { 
            //ошибка
        }        
    }

    void Server::sendListOfOnlineMembers(tgui::String nickname)
    {
        auto itClient = std::find_if(OnlineUsers.begin(), OnlineUsers.end(), [&](const ClientStruct &st1)->bool{
        if (nickname == st1.Nickname)
        {
            return true;
        }
        return false; });

        if (itClient->Socket.send(&OnlineUsers, sizeof(ClientStruct)* OnlineUsers.size()) != sf::Socket::Done ) 
        { 
            //ошибка
        }
    }

    void Server::sendNicknameNewClient(tgui::String nickname)
    {
        for(auto& user : OnlineUsers)
        {
            if (nickname == user.Nickname)
            {
                continue;
            }
            if(user.Socket.send(&nickname, nickname.length()) != sf::Socket::Done )
            {

            }
        }
    }
    
    void Server::sendMessageToOnlineUsers(MessageStruct msg)
    {
        sf::Packet packet;
        packet << static_cast<std::string>(msg.Nickname) << static_cast<std::string>(msg.Message);
        for(auto& user : OnlineUsers)
        {
            if (msg.Nickname == user.Nickname)
            {
                continue;
            }
            if(user.Socket.send(packet) != sf::Socket::Done)
            {

            }
        }
    }
    MessageStruct Server::receiveMessage()
    {
        sf::Packet packet;
        std::string nickname;
        std::string message;
        for(auto& user : OnlineUsers)
        {
            user.Socket.setBlocking(false);
            
            if(user.Socket.receive(packet) == sf::Socket::Done)
            {
                break;
            }
        }
        packet >> nickname >> message;
        MessageStruct messageStruct;
        messageStruct.Message = static_cast<tgui::String>(message);
        messageStruct.Nickname = static_cast<tgui::String>(nickname); 
        AllMessages.push_back(messageStruct);
        if (AllMessages.size() == MAX_COUNT_MESSAGES)
        {
            AllMessages.pop_front();
        }
        return messageStruct;
    }  
} // namespace chat