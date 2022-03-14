#include <ClientStruct.hpp>
#include <MessageStruct.hpp>
#include <iostream>
#include <vector>
class MyServer {
  private:
    std::vector<ClientStruct> AllUsers;
    std::vector<MessageStruct> AllMessage;

  public:
    MyServer(/* args */);
    ~MyServer();
};
