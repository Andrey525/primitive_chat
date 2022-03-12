#include "NetworkInteraction.hpp"

std::vector<MessageStructure> NetworkInteraction::Update()
{
    std::vector<MessageStructure> result;
    return result;
}

void NetworkInteraction::SendMSG(std::string msg)
{
    std::cout << "Я послал MSG" << msg << std::endl;
}
