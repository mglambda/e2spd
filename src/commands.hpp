
#ifndef __E2SPD_COMMANDS_HPP__
#define __E2SPD_COMMANDS_HPP__

#include <thread>

#include "State.hpp"
#include "utility.hpp"


inline void queueMsg(State &st, std::string w) {
  st.msgs.push(w);

  return;
}

inline void speakQueue(State &st, std::string dummy) {
	if(st.msgs.empty()) {
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

inline void speakChar(State& st, std::string w) {
	st.tts.sayChar(w);
}


inline void stopSpeaking(State &st, std::string dummy) { st.tts.stop(); }

inline void ttsSay(State &st, std::string w) { st.tts.say(w); }

inline void ttsSetSpeechRate(State &st, std::string w) {
	auto maybeRate = strToInt(w);
	if(!maybeRate) {
		return;
	}
	st.tts.setRate(*maybeRate);
}

inline void ttsSetPunctuation(State& st, std::string w) {
	auto maybeInt = strToInt(w);
	if(!maybeInt) {
	return;
}

	st.tts.setPunctuation(static_cast<SPDPunctuation>(*maybeInt));
}


inline void ttsSyncState(State& st, std::string w) {
//         punct, capitalize, allcaps, splitcaps, rate = re.split("\s+", data)
	
}

#endif