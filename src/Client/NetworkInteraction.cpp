#include "NetworkInteraction.hpp"

std::vector<MessageStructure> NetworkInteraction::Update() {
    std::vector<MessageStructure> result;
    return result;
}

void NetworkInteraction::SendMSG(tgui::String msg, tgui::String LoginName) {
    MessageStructure MsgStruct;
    MsgStruct.Messege = msg;
    MsgStruct.LoginName = LoginName;
    MsgStruct.now = time(NULL);
    //Послать на сервер
}
std::vector<tgui::String> NetworkInteraction::GetAllLoginName() {
    std::vector<tgui::String> AllLoginName;
    return AllLoginName;
}
