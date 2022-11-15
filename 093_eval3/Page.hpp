#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include <fstream>
#include <iostream>
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

 public:
  Page() : type(N), text(""), choices(std::vector<Choice>()) {}

  Page(const std::string & dirName, const std::string & str) :
      type(N), text(""), choices(std::vector<Choice>()) {
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

  // Add a new choice to this page.
  void addChoice(std::size_t d, const std::string & str) {
    if (type == W || type == L) {
      std::cerr << "Can't add choice to a WIN/LOSS page!\n";
      throw std::exception();
    }
    Choice newChoice(d, str);
    choices.push_back(newChoice);
  }

  // Output the page.
  friend std::ostream & operator<<(std::ostream & s, const Page & rhs) {
    s << rhs.text << std::endl;
    if (rhs.type == W) {
      s << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (rhs.type == L) {
      s << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    else {
      s << "What would you like to do?" << std::endl << std::endl;
      for (std::size_t i = 0; i < rhs.choices.size(); i++) {
        s << " " << i + 1 << ". " << rhs.choices[i];
      }
    }
    return s;
  }
};

#endif
