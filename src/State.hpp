
#ifndef __E2SPD_STATE_H__
#define __E2SPD_STATE_H__

#include <functional>
#include <string>
#include <vector>

#include "Queue.hpp"
#include "TTS.hpp"

class State {
private:
    typedef std::string command_t;

    typedef std::function<void(State&, const std::string)> command_handler_t;
    struct command_entry_t {
        command_t cmd;
        command_handler_t handler;
    };

    struct multiline_data {
        command_t cmd;
        std::string data;
    };

    typedef std::optional<multiline_data> multiline_mode_t;

public:
    typedef std::vector<command_entry_t> commands_t;
    typedef Concurrent::Queue<std::string> queue_t;

private:
    commands_t commands;
    multiline_mode_t maybeMultiLineMode;

public:
    TTS tts;
    queue_t msgs;

public:
    State(commands_t&& commands, TTS&& tts)
        : commands(std::move(commands)), tts(std::move(tts)) {}

    bool handleCommand(command_t cmd, std::string data);
    inline bool isInMultiLineMode() const {
        return this->maybeMultiLineMode.has_value();
    }
    void beginMultiLineMode(const command_t cmd, const std::string data);
    void continueMultiLineMode(const std::string data);
    multiline_data endMultiLineMode(const std::string finalData);
};

#endif
