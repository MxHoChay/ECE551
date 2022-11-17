#include <cstdlib>
#include <iostream>
#include <string>

#include "Story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Please input one directory path!\n";
    throw std::exception();
  }
  std::string dirName(argv[1]);
  Story mystory;
  mystory.parseStory(dirName + "/");
  mystory.verifyTheStory();
  if (mystory.readStory("&&&")) {
    return EXIT_SUCCESS;
  }
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, stdin) > 0) {
    std::string str(line);
    if (str[str.length() - 1] == '\n') {
      str.erase(str.length() - 1);
    }
    free(line);
    line = NULL;
    if (mystory.readStory(str)) {
      return EXIT_SUCCESS;
    }
  }
  free(line);
  return EXIT_SUCCESS;
}
