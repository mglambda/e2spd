

#ifndef EMACS_SDP_TTS_CPP
#define E2SPD_TTS_CPP

#include <libspeechd.h>
#include <memory>
#include <string>

#include "utility.hpp"
class TTS {
    // private:
public:
    std::unique_ptr<SPDConnection> con;

public:
    void say(std::string w);
    void sayChar(std::string w);
    void stop();
    void setRate(int rate);
    void setPunctuation(SPDPunctuation level);
    void setSplitCapitalization(bool splitcaps);
    void setCapitalization(SPDCapitalLetters mode);
    TTS()
        : con(spd_open("e2spd", "e2spd-con", "e2spd-user", SPD_MODE_THREADED)) {
    }

    TTS(TTS&) = delete;
    TTS(const TTS&) = delete;
    TTS& operator=(TTS&) = delete;
    TTS& operator=(const TTS&) = delete;
    inline TTS(TTS&& tts) : con(std::move(tts.con)) {}

    inline TTS& operator=(TTS&& tts) {
        this->con = std::move(tts.con);
        return *this;
    }

    inline ~TTS() {
        if (this->con) {
            spd_close(con.get());
            this->con.release();
        }
    }
};
#endif
