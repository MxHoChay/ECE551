#include <string.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "Story.hpp"

int main(int argc, char ** argv) {
  Story mystory;
  if (argc != 2) {
    std::cerr << "Please input the directory path!\n";
    throw std::exception();
  }
  std::string dirName(argv[1]);
  mystory.parseStory(dirName + "/");
  std::cout << mystory;
  return EXIT_SUCCESS;
}
