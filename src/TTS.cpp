

#include "TTS.hpp"
#include "log.hpp"
#include <string>

using namespace std;

void TTS::say(string w) { spd_say(this->con.get(), SPD_TEXT, w.c_str()); }

void TTS::sayChar(std::string w) {
    //	auto n = spd_char(this->con.get(), SPD_IMPORTANT, w.c_str());
    auto n = spd_say(this->con.get(), SPD_TEXT, w.c_str());
}

void TTS::stop() {
    if (spd_stop(this->con.get())) {
        log<Debug>("libspeechd error in spd_stop");
    }
}

void TTS::setRate(int rate) { spd_set_voice_rate(this->con.get(), rate); }

void TTS::setPunctuation(SPDPunctuation level) {
    /*	SPD_PUNCT_ALL = 0,
        SPD_PUNCT_NONE = 1,
        SPD_PUNCT_SOME = 2,
        SPD_PUNCT_MOST = 3	 */
    log<Debug>("setting punct to", level);
    if (spd_set_punctuation(this->con.get(), level);) {
        log<Debug>("libspeechd error in spd_set_punctuation");
    }
}

void TTS::setSplitCapitalization(bool splitcaps) {
    // FIXME: this doesn't seem to be a native flag in spd. This might be a bit
    // hacky.
    if (splitcaps) {
        this->setCapitalization(SPD_CAP_ICON);
    } else {
        this->setCapitalization(SPD_CAP_NONE);
    }
}

void TTS::setCapitalization(SPDCapitalLetters mode) {
    /* 	SPD_CAP_NONE = 0,
SPD_CAP_SPELL = 1,
SPD_CAP_ICON = 2 */

    if (spd_set_capital_letters(this->con.get(), mode);) {
        log<Debug>("libspeechd error in spd_capital_letter");
    }
}
