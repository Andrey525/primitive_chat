#include <iostream>
#include <vector>
#include "NetworkInteraction.hpp"

class MainWindow
{
private:
    std::string LoginName;
    std::vector<MessageStructure> AllMessage;
public:
    MainWindow(std::string LoginName);
    ~MainWindow() = default;
};