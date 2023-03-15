#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <string>
#include <vector>

namespace ilox {

void DebugView(std::vector<std::string> debug_messages);

void DebugMessage(const char *message);

std::vector<std::string> ReadScriptFile(std::string filename);

} // namespace ilox

#endif