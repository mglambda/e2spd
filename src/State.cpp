

#include "State.hpp"
#include <algorithm>

bool State::handleCommand(std::string cmd, std::string data) {
  // returns false on unrecognized command
  auto i = std::find_if(
      this->commands.begin(), this->commands.end(),
      [&](const command_entry_t &entry) { return entry.cmd == cmd; });

  if (i == this->commands.end()) {
    return false;
  }
  i->handler(*this, data);
  return true;
}
