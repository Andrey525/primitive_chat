#include <iostream>
#include <vector>
#include "ClientStruct.hpp"
#include "MessageStructure.hpp"
class MyServer
{
private:
    std::vector<ClientStruct> AllUsers;
    std::vector<MessageStructure> AllMessage;
public:
    MyServer(/* args */);
    ~MyServer();

    
};

