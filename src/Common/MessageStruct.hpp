#pragma once

#include <TGUI/TGUI.hpp>

namespace chat {

struct MessageStruct {
    tgui::String Nickname;
    tgui::String Message;
    MessageStruct() = default;
    MessageStruct(tgui::String nickname, tgui::String message)
        : Nickname(nickname), Message(message) {}
};

} // namespace chat