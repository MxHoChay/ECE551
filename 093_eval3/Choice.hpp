#ifndef __CHOICE_HPP__
#define __CHOICE_HPP__

#include <iostream>
#include <string>
#include <vector>

/**
 * This class is used as a single choice in each page.
 * For each choice, we have the destnation page and text as fields.
 */

class Choice {
  size_t dest;
  std::string text;

 public:
  Choice() : dest(0), text("") {}
  Choice(size_t d, const std::string & str) : dest(d), text(str) {}

  // To check each page referenced by this choice is valid.
  void verifyTheChoice(size_t max, std::vector<bool> & refTable) {
    if (dest >= max) {
      std::cerr << "Invalid reference!\n";
      throw std::exception();
    }
    refTable[dest] = true;
  }

  size_t getDest() const { return dest; }

  // Output the choice
  friend std::ostream & operator<<(std::ostream & s, const Choice & rhs) {
    s << rhs.text << std::endl;
    return s;
  }
};

#endif
