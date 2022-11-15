#include <cstdlib>

#include "Story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Please input one directory path!\n";
    throw std::exception();
  }
  Story mystory;
  std::string dirName(argv[1]);
  mystory.parseStory(dirName + "/");
  mystory.verifyTheStory();
  mystory.winTheStory();
  return EXIT_SUCCESS;
}
