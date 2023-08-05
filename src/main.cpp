
#ifndef E2SPD_MAIN_CPP
#define E2SPD_MAIN_CPP

#include <iostream>
#include <libspeechd.h>
#include <string>
#include <vector>

#include "State.hpp"
#include "commands.hpp"
#include "log.hpp"
#include "utility.hpp"

State::commands_t commands = {{"s", stopSpeaking},
                              {"l", speakChar},
                              {"q", queueMsg},
                              {"d", speakQueue},
                              {"tts_set_punctuations", ttsSetPunctuation},
                              {"tts_split_caps", ttsSetSplitCaps},
                              {"tts_set_speech_rate", ttsSetSpeechRate},

                              {"tts_sync_state", ttsSyncState},
                              {"tts_say", ttsSay}};

std::ofstream Debug::destination("/tmp/e2spd.debug.log",
                                 std::ios::out | std::ios::trunc);
std::ofstream Error::destination("/tmp/e2spd.error.log",
                                 std::ios::out | std::ios::trunc);
std::ofstream Raw::destination("/tmp/e2spd.raw.log",
                               std::ios::out | std::ios::trunc);

int main(int argc, char** argv) {
    using namespace std;
    log<Debug>("Started e2spd.");

    string line("");
    auto st = State(std::move(commands), TTS());
    st.tts.say("e2spd running.");

    while (true) {
        getline(cin, line);
        log<Raw>(line);

        auto [cmd, data] = split1(line, " ");
        log<Debug>(cmd, " with data: ", data);

        if (!st.handleCommand(cmd, data)) {
            log<Error>("unrecognized command: ", cmd);
            st.tts.say(line);
        }
    }

    return 0;
}

#endif
