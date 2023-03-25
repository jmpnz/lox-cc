#include "debug.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace lox {

auto DebugView(const std::vector<std::string> &debug_messages) -> void {
  for (auto &msg : debug_messages) {
    std::cout << msg << '\n';
  }
  std::cout << std::endl;
}

auto DebugMessage(const char *message) -> void { std::cout << message << '\n'; }

auto ReadScriptFile(const std::string &filename) -> std::vector<std::string> {
  std::ifstream file{filename};

  if (!file.is_open()) {
    std::cerr << "Couldn't read file: " << filename << '\n';
    exit(1);
  }

  std::vector<std::string> lines;
  for (std::string line; std::getline(file, line);) {
    lines.push_back(line);
  }

  return lines;
}

} // namespace lox
