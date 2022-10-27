#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::vector<std::string> arr;
    std::string str;
    while (true) {
      std::getline(std::cin, str);
      if (str == "") {
        break;
      }
      arr.push_back(str);
    }
    std::sort(arr.begin(), arr.end());
    std::vector<std::string>::iterator it = arr.begin();
    while (it != arr.end()) {
      std::cout << *it << std::endl;
      ++it;
    }
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::vector<std::string> arr;
      std::string str;
      std::ifstream file;
      file.open(argv[i], std::ifstream::in);
      if (!file.is_open()) {
        std::cerr << "Invalid file name!" << std::endl;
        exit(EXIT_FAILURE);
      }
      while (std::getline(file, str)) {
        arr.push_back(str);
      }
      std::sort(arr.begin(), arr.end());
      std::vector<std::string>::iterator it = arr.begin();
      while (it != arr.end()) {
        std::cout << *it << std::endl;
        ++it;
      }
    }
  }
  return EXIT_SUCCESS;
}
