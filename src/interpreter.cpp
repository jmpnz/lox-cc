#include <iostream>
namespace lox {

void RunPrompt() {
  std::cout << "This is an lox prompt" << '\n';
  while (true) {
    std::string line;
    std::cout << "> ";
    std::getline(std::cin, line);
    if (line == "exit") {
      exit(1);
    } else {
      std::cout << line << '\n';
    }
  }
}

} // namespace lox
