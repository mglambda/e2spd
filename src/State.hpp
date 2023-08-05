
#ifndef __E2SPD_STATE_H__
#define __E2SPD_STATE_H__

#include <functional>
#include <string>
#include <vector>

#include "TTS.hpp"
#include "Queue.hpp"

class State {
private:
	typedef std::function<void(State&, std::string)> command_handler_t;
  struct command_entry_t {
    std::string cmd;
	  command_handler_t handler;
  };
public:
		  typedef std::vector<command_entry_t> commands_t;
	typedef Concurrent::Queue<std::string> queue_t;
private:
  commands_t commands;

public:
  TTS tts;
	queue_t msgs;

public:
	State(commands_t&& commands, TTS&& tts) : commands(std::move(commands)), tts(std::move(tts)) {}

  bool handleCommand(std::string cmd, std::string data);
};

#endif
