#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void DefineAST(std::string output_dir, std::string base_name,
               std::vector<std::string> types) {
  std::string path = output_dir + "/" + base_name + ".cpp";
  std::ofstream f(path);

  f << "#include<vector> \n";
  std::cout << "Flushing file ?";
  f.flush();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: generate_ast <output dir>" << std::endl;
  }
  std::string output_dir(argv[1]);
  std::cout << output_dir << std::endl;

  std::vector<std::string> types = {
      "Grouping: Expr expression",
  };
  DefineAST(output_dir, "Grouping", types);
}