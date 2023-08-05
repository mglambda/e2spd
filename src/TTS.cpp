

#include "TTS.hpp"
#include <string>

using namespace std;

void TTS::say(string w) { spd_say(this->con.get(), SPD_TEXT, w.c_str()); }

void TTS::sayChar(std::string w) {

//	auto n = spd_char(this->con.get(), SPD_IMPORTANT, w.c_str());
	auto n = spd_say(this->con.get(), SPD_TEXT, w.c_str());

}

void TTS::stop() {
	spd_stop(this->con.get());
}


void TTS::setRate(int rate) {
	spd_set_voice_rate(this->con.get(), rate);
}

void TTS::setPunctuation(SPDPunctuation level) {
/*	SPD_PUNCT_ALL = 0,
	SPD_PUNCT_NONE = 1,
	SPD_PUNCT_SOME = 2,
	SPD_PUNCT_MOST = 3	 */

	spd_set_punctuation(this->con.get(), level);

}
