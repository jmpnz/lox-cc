#include "debug.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace lox {

void DebugView(std::vector<std::string> debug_messages) {
  for (auto &msg : debug_messages) {
    std::cout << msg << '\n';
  }
  std::cout << std::endl;
}

void DebugMessage(const char *message) { std::cout << message << '\n'; }

std::vector<std::string> ReadScriptFile(std::string filename) {
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
