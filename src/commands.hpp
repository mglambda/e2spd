
#ifndef __E2SPD_COMMANDS_HPP__
#define __E2SPD_COMMANDS_HPP__

#include <boost/algorithm/string.hpp>
#include <thread>

#include "State.hpp"
#include "log.hpp"
#include "utility.hpp"

inline void queueMsg(State& st, std::string w) {
    st.msgs.push(w);

    return;
}

inline void speakQueue(State& st, std::string dummy) {
    if (st.msgs.empty()) {
        return;
    }

    auto t = std::thread([&]() {
        auto w = std::string("");

        while (!st.msgs.empty()) {
            w.append(st.msgs.pop());
        }
        st.tts.say(w);
    });
    t.detach();
    return;
}

inline void speakChar(State& st, std::string w) { st.tts.sayChar(w); }

inline void stopSpeaking(State& st, std::string dummy) { st.tts.stop(); }

inline void ttsSay(State& st, std::string w) { st.tts.say(w); }

inline void ttsSetSpeechRate(State& st, std::string w) {
    auto maybeRate = strToInt(w);
    if (!maybeRate) {
        return;
    }
    st.tts.setRate(*maybeRate);
}

inline void ttsSetPunctuation(State& st, std::string w) {
    auto v = trim(w);
    auto punct = std::optional<SPDPunctuation>();
    if (v == "all") {
        punct = std::make_optional(SPD_PUNCT_ALL);
    } else if (v == "none") {
        punct = std::make_optional(SPD_PUNCT_NONE);
    } else if (v == "some") {
        punct = std::make_optional(SPD_PUNCT_SOME);
    } else if (v == "most") {
        punct = std::make_optional(SPD_PUNCT_MOST);
    }

    if (punct) {
        st.tts.setPunctuation(*punct);
        return;
    }

    log<Error>("Attempt to set punctuation to unsupported mode: ", v);
} /* end ttsSetPunctuation */

inline void ttsSetSplitCaps(State& st, std::string w) {
    auto maybeSplitCapsInt = strToInt(w);

    if (!maybeSplitCapsInt) {
        log<Error>("Attempt to set spli caps to invalid mode: ", w);
        return;
    }

    st.tts.setSplitCapitalization(*maybeSplitCapsInt);
}

inline void ttsSyncState(State& st, std::string w) {
    //         punct, splitcaps 1/0, caps 1/0, rate

	
}

#endif
