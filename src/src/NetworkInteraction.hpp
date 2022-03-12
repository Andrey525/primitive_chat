#pragma once
#include <iostream>
#include <vector>
#include "MessageStructure.hpp"

class NetworkInteraction
{
public:
    NetworkInteraction() = default;
    ~NetworkInteraction() = default;

    std::vector<MessageStructure> static Update();
    void static SendMSG(std::string msg);
};
