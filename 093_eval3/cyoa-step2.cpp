#include <cstdlib>
#include <iostream>
#include <string>

#include "MyException.hpp"
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
  // Get user input.
  std::string str;
  while (!std::cin.eof()) {
    std::cin >> str;
    if (mystory.readStory(str)) {
      return EXIT_SUCCESS;
    }
  }
  throw UnFinished();
  return EXIT_FAILURE;
}
