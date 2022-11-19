#ifndef __CHOICE_HPP__
#define __CHOICE_HPP__

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "MyException.hpp"

/**
 * This class is used as a single choice in each page.
 * For each choice, we have the destnation page and text as fields.
 */

class Choice {
  size_t dest;
  std::string text;
  std::string var;
  long int value;

 public:
  Choice() : dest(0), text(std::string("")), var(std::string("")), value(-1) {}
  // Construct the choice with condition.
  Choice(size_t d, const std::string & str, const std::string & cond) :
      dest(d), text(str), var(std::string("+Nothing+")), value(-1) {
    if (cond == "") {
      return;
    }
    size_t equal = cond.find_first_of('=');
    var = cond.substr(0, equal);
    value = std::strtol(cond.substr(equal + 1).c_str(), NULL, 10);
    if (errno != 0) {
      throw NumOutOfRange();
    }
  }

  // To check each page referenced by this choice is valid.
  void verifyTheChoice(size_t max, std::vector<bool> & refTable) {
    if (dest >= max) {
      std::cerr << "Invalid reference!\n";
      throw std::exception();
    }
    refTable[dest] = true;
  }

  // To check if the choice meets the variable condition
  bool isAvaliable(const std::map<std::string, long int> & storyVar) const {
    if (var == "+Nothing+") {
      return true;
    }
    try {
      if (storyVar.at(var) == value) {
        return true;
      }
    }
    catch (std::exception & e) {
      if (value == 0) {
        return true;
      }
    }
    return false;
  }

  // Return the destpage of this choice.
  size_t getDest(const std::map<std::string, long int> & storyVar) const {
    if (isAvaliable(storyVar)) {
      return dest;
    }
    else {
      return -1;
    }
  }

  // Print the choice and the text. If the choice is unavailable under the condition, then print <UNAVAILABLE>.
  void readChoice(std::ostream & s,
                  const std::map<std::string, long int> & storyVar,
                  bool isUserReading = false) const {
    if (!isUserReading || isAvaliable(storyVar)) {
      s << text << std::endl;
    }
    else {
      s << "<UNAVAILABLE>\n";
    }
  }

  // Output the choice
  friend std::ostream & operator<<(std::ostream & s, const Choice & rhs) {
    rhs.readChoice(s, std::map<std::string, long int>());
    return s;
  }
};

#endif
