#ifndef __STORY_HPP__
#define __STORY_HPP__

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Page.hpp"

/**
 * This class is the whole story.
 * A story consists of multiple pages.
 * This class can parse the information in story.txt and make it a final story.
 */

class Story {
  std::vector<Page> pages;

  // Convert string to size_t.
  size_t myaTol(const std::string & str) {
    if (str.length() == 0 || str[0] < '0' || str[0] > '9') {
      std::cerr << "Invalid page number!\n";
      throw std::exception();
    }
    size_t max = -1;
    size_t res = 0;
    for (size_t i = 0; i < str.length(); i++) {
      if (str[i] < '0' || str[i] > '9') {
        return res;
      }
      size_t digit = str[i] - '0';
      if (res > max / 10 || (res == max / 10 && digit > max % 10)) {
        std::cerr << "Page number excced size_t!\n";
        throw std::exception();
      }
      res = res * 10 + digit;
    }
    return res;
  }

 public:
  Story() : pages(std::vector<Page>()) {}

  void parseStory(const std::string & dirName) {
    FILE * f = fopen((dirName + "story.txt").c_str(), "r");
    if (f == NULL) {
      std::cerr << "No story.txt!\n";
      throw std::exception();
    }
    char * line = NULL;
    size_t sz = 0;
    while (getline(&line, &sz, f) > 0) {
      std::string strline(line);
      if (strline[strline.length() - 1] == '\n') {
        strline.erase(strline.length() - 1);
      }
      // To check if the line is blank.
      bool isBlank = true;
      for (size_t i = 0; i < strline.length(); i++) {
        if (strline[i] != ' ' || strline[i] != '\n') {
          isBlank = false;
          break;
        }
      }
      // If the line is blank, ignore it and goto the next line.
      if (isBlank) {
        continue;
      }
      size_t at_index = strline.find_first_of('@', 0);
      if (at_index == std::string::npos) {
        size_t first = strline.find_first_of(':', 0);
        size_t second = strline.find_first_of(':', first + 1);
        if (first == std::string::npos || second == std::string::npos) {
          std::cerr << "Invalid choice line: Lack two ':'s!";
          throw std::exception();
        }
        size_t pageNum = myaTol(strline.c_str());
        size_t destPageNum = myaTol(strline.substr(first + 1).c_str());
        // To check the choice is allowed
        if (pageNum >= pages.size()) {
          std::cerr << "Invalid page operation:\n";
          std::cerr << pageNum << " " << destPageNum << " " << pages.size() << std::endl;
          throw std::exception();
        }
        pages[pageNum].addChoice(destPageNum, strline.substr(second + 1));
      }
      else {
        size_t pageNum = myaTol(strline.c_str());
        if (pageNum != pages.size()) {
          std::cerr << "Wrong page order!\n";
          throw std::exception();
        }
        Page newPage(dirName, strline.substr(at_index + 1));
        pages.push_back(newPage);
      }
    }
    free(line);
    fclose(f);
  }

  friend std::ostream & operator<<(std::ostream & s, const Story & rhs) {
    for (std::size_t i = 0; i < rhs.pages.size(); i++) {
      s << "Page " << i << std::endl;
      s << "==========" << std::endl;
      s << rhs.pages[i];
    }
    return s;
  }
};

#endif
