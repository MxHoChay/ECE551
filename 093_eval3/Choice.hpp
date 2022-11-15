#ifndef __CHOICE_HPP__
#define __CHOICE_HPP__

#include <iostream>
#include <string>

/**
 * This class is used as a single choice in each page.
 * For each choice, we have the destnation page and text as fields.
 */

class Choice {
  std::size_t dest;
  std::string text;

 public:
  Choice() : dest(0), text("") {}
  Choice(std::size_t d, const std::string & str) : dest(d), text(str) {}

  // Output the choice
  friend std::ostream & operator<<(std::ostream & s, const Choice & rhs) {
    s << rhs.text << std::endl;
    return s;
  }
};

#endif
