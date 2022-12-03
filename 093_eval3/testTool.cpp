#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "Tool.hpp"

int main(void) {
  //FILE * f = fopen("testTool.txt", "r");
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, stdin) > 0) {
    std::string str(line);
    if (str[str.length() - 1] == '\n') {
      str.erase(str.length() - 1);
    }
    //std::stringstream ss(str);
    //std::string text;
    //ss >> text;
    //int pattern;
    //ss >> pattern;
    if (isMatch(str, 1)) {
      std::cout << "true\n";
    }
    else {
      std::cout << "false\n";
    }
  }
  free(line);
  //fclose(f);
  return EXIT_SUCCESS;
}
