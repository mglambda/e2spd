
#ifndef __E2SPD_COMMANDS_HPP__
#define __E2SPD_COMMANDS_HPP__

#include <boost/algorithm/string.hpp>
#include <thread>

#include "State.hpp"
#include "log.hpp"
#include "utility.hpp"

inline void queueMsg(State& st, const std::string w) {
    st.msgs.push(w);

    return;
}

inline void queueCode(State& st, const std::string w) {
    // FIXME: stub. need to find out what codes actually do
    st.msgs.push(w);
}
inline void speakQueue(State& st, const std::string dummy) {
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

inline void speakChar(State& st, const std::string w) { st.tts.sayChar(w); }

inline void stopSpeaking(State& st, const std::string dummy) { st.tts.stop(); }

inline void ttsSay(State& st, const std::string w) { st.tts.say(w); }

inline void ttsSetSpeechRate(State& st, const std::string w) {
    auto maybeRate = strToInt(w);
    if (!maybeRate) {
        return;
    }

    log<Debug>("Setting rate to ", *maybeRate);
    st.tts.setRate(*maybeRate);
}

inline void ttsSetPunctuation(State& st, const std::string w) {
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

inline void ttsSetSplitCaps(State& st, const std::string w) {
    auto maybeSplitCapsInt = strToInt(w);

    if (!maybeSplitCapsInt) {
        log<Error>("Attempt to set spli caps to invalid mode: ", w);
        return;
    }

    log<Debug>("Setting splitcaps to ", *maybeSplitCapsInt);
    st.tts.setSplitCapitalization(*maybeSplitCapsInt);
}

inline void ttsSyncState(State& st, const std::string w) {
    auto args = std::vector<std::string>{};
    boost::algorithm::split(args, w,
                            [](const char delim) { return delim == ' '; });
    if (args.size() < 4) {
        log<Error>("error trying to sync tts state: Not enough arguments.");
        return;
    }

    auto punct = args[0];                     // "none", "some", or "all"
    auto maybeSplitCaps = strToInt(args[1]);  // "0" or "1"
    auto maybeCaps = strToInt(args[2]);       // "0" or "1"
    auto rate = args[3];                      // string representing small int

    ttsSetPunctuation(st, punct);
    ttsSetSpeechRate(st, rate);

    if (!maybeSplitCaps || !maybeCaps) {
        log<Error>("error trying to sync state: Malformed arguments.");
        return;
    }

    bool splitcaps = *maybeSplitCaps;
    bool caps = *maybeCaps;

    /* as far as I'm aware speech-dispatcher doesn't track splitcaps seperately,
     * instead combining splitcaps and caps into 3 capitalization submodes. So
     * we have to repackage the arguments a little here. */
    if (splitcaps) {
        log<Debug>("Setting caps to icon");
        st.tts.setCapitalization(SPD_CAP_ICON);
        return;
    }

    if (caps) {
        log<Debug>("Setting caps to spell");
        st.tts.setCapitalization(SPD_CAP_SPELL);
    } else {
        log<Debug>("Setting caps to none");
        st.tts.setCapitalization(SPD_CAP_NONE);
    }
}

inline void ttsSetLanguage(State& st, const std::string w) {
    // command is in the form 'set_lange LANGUAGE SAY_IT', ofc command is not
    // part of w
    // FIXME: don't know what say_it means
    log<Debug>("setting language to ", w);
    auto [lang, sayIt] = split1(w, " ");
    st.tts.setLanguage(lang);
}
#endif
