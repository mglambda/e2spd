

#include "State.hpp"
#include <algorithm>

bool State::handleCommand(command_t cmd, std::string data) {
    // returns false on unrecognized command
    log<Debug>(cmd, " with data: ", data);

    auto i = std::find_if(
        this->commands.begin(), this->commands.end(),
        [&](const command_entry_t& entry) { return entry.cmd == cmd; });

    if (i == this->commands.end()) {
        log<Error>("unrecognized command: ", cmd);
        return false;
    }
    i->handler(*this, data);
    return true;
}

void State::beginMultiLineMode(const command_t cmd, const std::string data) {
    if (this->maybeMultiLineMode) {
        log<Debug>(
            "Warning: enabling multiline moade in State when it is already "
            "active.");
        return;
    }

    this->maybeMultiLineMode =
        std::make_optional(State::multiline_data{cmd, data});
}

void State::continueMultiLineMode(const std::string data) {
    if (!this->maybeMultiLineMode) {
        log<Debug>(
            "warning: multiline mode continued when multiline mode is not "
            "active.");
        return;
    }
    this->maybeMultiLineMode->data.append(data);
}

State::multiline_data State::endMultiLineMode(const std::string finalData) {
    if (!this->maybeMultiLineMode) {
        log<Debug>("Warning: Disabling multi line mode when it is not active.");
        return State::multiline_data{"", finalData};
    }
    auto result = *(this->maybeMultiLineMode);
    result.data.append(finalData);
    this->maybeMultiLineMode.reset();
    return result;
}
