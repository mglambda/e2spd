

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
                              {"c", queueCode},
                              {"d", speakQueue},
                              {"tts_set_punctuations", ttsSetPunctuation},
                              {"tts_split_caps", ttsSetSplitCaps},
                              {"tts_set_speech_rate", ttsSetSpeechRate},
                              {"set_lang", ttsSetLanguage},
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

        if (st.isInMultiLineMode()) {
            auto maybeData = upToDelimiter(line, "}");
            if (maybeData) {
                // right brace was found -> end multiline mode and process
                // collected data
                log<Debug>("main: ending multiline mode.");
                auto [cmd, data] = st.endMultiLineMode(*maybeData);
                st.handleCommand(cmd, data);
                continue;
            }
            // no end delimiter was found -> continue reading data in
            // multiline mode
            log<Debug>("main: continueing multiline mode.");
            st.continueMultiLineMode(line);
            continue;
        }

        auto maybeData = afterDelimiter(line, "{");
        if (maybeData) {
            // we're not in multiline mode and a left delimiter was found ->
            if (maybeData->back() == '}') {
                // brace opened and closed on the same line -> just handle data
                // with cmd
                log<Debug>("main: processing single line");
                auto [cmd, _w] = split1(line, " ");
                st.handleCommand(cmd,
                                 maybeData->substr(0, maybeData->size() - 1));
                continue;
            } else {
                // a left brace was found but no right brace -> enter multiline
                // mode
                log<Debug>("main: begin multiline mode.");
                auto [cmd, _w] = split1(line, " ");
                st.beginMultiLineMode(cmd, *maybeData);
                continue;
            }
        }
        // no braces -> just treat everything after first space as data.
        // This happens with e.g. tts_sync_state
        log<Debug>("main: processing raw line (no braces).");
        auto [cmd, data] = split1(line, " ");
        st.handleCommand(cmd, data);
    }

    return 0;
}
