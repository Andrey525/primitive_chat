#include "NetworkInteraction.hpp"

std::vector<MessageStructure> NetworkInteraction::Update()
{
    std::vector<MessageStructure> result;
    return result;
}

void NetworkInteraction::SendMSG(std::string msg, std::string LoginName)
{
    MessageStructure MsgStruct;
    MsgStruct.Messege = msg;
    MsgStruct.LoginName = LoginName;
    MsgStruct.now = time(NULL);
    //Послать на сервер
}
std::vector<std::string> NetworkInteraction::GetAllLoginName()
{
    std::vector<std::string> AllLoginName;
    return AllLoginName;
}
