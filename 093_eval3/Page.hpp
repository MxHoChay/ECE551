#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Choice.hpp"

/**
 * This class is used as a single page in the whole stroy.
 * Each page has its type: N, W, L.
 * Also, each page has its text.
 * Besides, each page has multiple choices.
 */

enum PageType { N, W, L };

class Page {
  PageType type;
  std::string text;
  std::vector<Choice> choices;
  std::map<std::string, long int> variables;

 public:
  Page() : type(N) {}

  Page(const std::string & dirName, const std::string & str) : type(N) {
    // Set the type of the page.
    switch (str[0]) {
      case 'N':
        type = N;
        break;
      case 'W':
        type = W;
        break;
      case 'L':
        type = L;
        break;
    }
    setText(dirName + str.substr(2));
  }

  // Open the file and get the text of this page.
  void setText(const std::string & filename) {
    std::ifstream input;
    input.open(filename.c_str(), std::ifstream::in);
    if (!input.is_open()) {
      std::cerr << "No page file! File path :" << filename << std::endl;
      throw std::exception();
    }
    std::stringstream buffer;
    buffer << input.rdbuf();
    text = buffer.str();
    input.close();
  }

  size_t getSize() { return choices.size(); }

  bool isWin() { return type == W; }

  bool isLose() { return type == L; }

  // Add a new choice to this page.
  void addChoice(std::size_t d, const std::string & str, const std::string & condition) {
    if (type == W || type == L) {
      std::cerr << "Can't add choice to a WIN/LOSS page!\n";
      throw std::exception();
    }
    Choice newChoice(d, str, condition);
    choices.push_back(newChoice);
  }

  // Set value to the variable
  void addVar(const std::string & str) {
    size_t equal = str.find_first_of('=');
    std::string var = str.substr(0, equal);
    long int value = (long int)std::stoll(str.substr(equal + 1));
    if ((long long)value != std::stoll(str.substr(equal + 1))) {
      std::cerr << "Invalid variable value!\n";
      throw std::exception();
    }
    variables[var] = value;
  }

  // Update global variables when moving to this page.
  void updateVar(std::map<std::string, long int> & storyVar) {
    for (std::map<std::string, long int>::iterator it = variables.begin();
         it != variables.end();
         ++it) {
      storyVar[it->first] = it->second;
    }
  }

  // To check if each page referenced by this page is valid.
  void verifyThePage(size_t max, std::vector<bool> & refTable) {
    for (size_t i = 0; i < choices.size(); i++) {
      choices[i].verifyTheChoice(max, refTable);
    }
  }

  size_t getNext(size_t next, const std::map<std::string, long int> & storyVar) {
    return choices[next - 1].getDest(storyVar);
  }

  void readPage(std::ostream & s,
                const std::map<std::string, long int> & storyVar,
                bool isUserReading = false) const {
    s << text << std::endl;
    if (type == W) {
      s << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (type == L) {
      s << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    else {
      s << "What would you like to do?" << std::endl << std::endl;
      for (std::size_t i = 0; i < choices.size(); i++) {
        s << " " << i + 1 << ". ";
        choices[i].readChoice(std::cout, storyVar, isUserReading);
      }
    }
    if (isUserReading && type != N) {
      exit(EXIT_SUCCESS);
    }
  }

  friend std::ostream & operator<<(std::ostream & s, const Page & rhs) {
    rhs.readPage(s, rhs.variables);
    return s;
  }
};

#endif