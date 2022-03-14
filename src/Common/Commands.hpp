#pragma once

namespace chat {

enum Commands {
    NEW_CONNECTION,
    NEW_MSG,
    REQUEST_NICKNAMES_LIST,
    REQUEST_LAST_MESSAGES,
    REMOVE_CLIENT
};

} // namespace chat