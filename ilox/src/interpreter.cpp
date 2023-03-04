#include <iostream>
namespace ilox {

void RunPrompt() {
  std::cout << "This is an ilox prompt" << '\n';
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

} // namespace ilox
