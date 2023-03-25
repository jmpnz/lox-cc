#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <string>
#include <vector>

namespace lox {

auto DebugView(const std::vector<std::string> &debug_messages) -> void;

auto DebugMessage(const char *message) -> void;

auto ReadScriptFile(const std::string &filename) -> std::vector<std::string>;

} // namespace lox

#endif
