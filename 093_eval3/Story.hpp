#ifndef __STORY_HPP__
#define __STORY_HPP__

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "Page.hpp"

/**
 * This class is the whole story.
 * A story consists of multiple pages.
 * This class can parse the information in story.txt and make it a final story.
 */

class Story {
  std::vector<Page> pages;
  size_t nowPage;
  std::map<std::string, long int> variables;

  // Convert string to size_t.
  size_t myaTol(const std::string & str, bool isUser = false) {
    // To make sure there is no other character in the user's input.
    if (isUser && !std::regex_match(str, std::regex("\\d+"))) {
      return 0;
    }
    if (str.length() == 0 || str[0] == '-') {
      std::cerr << "Invalid number! Any number should fit in size_t!\n";
      throw std::exception();
    }
    return (size_t)std::stoull(str);
  }

  // Try to make a choice and enter that page.
  bool tryPage(size_t pageNum,
               std::vector<bool> & visitTable,
               std::vector<std::pair<size_t, size_t> > & path) {
    if (visitTable[pageNum]) {
      return false;
    }
    // If there is a path, then print it out.
    if (pages[pageNum].isWin()) {
      for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i].first << "(" << path[i].second << "),";
      }
      std::cout << pageNum << "(win)\n";
      return true;
    }
    else if (pages[pageNum].isLose()) {
      return false;
    }
    // Read this page and try the next one.
    visitTable[pageNum] = true;
    bool hasPath = false;
    for (size_t i = 0; i < pages[pageNum].getSize(); i++) {
      size_t nextPage = pages[pageNum].getNext(i + 1, variables);
      std::pair<size_t, size_t> newpair(pageNum, i + 1);
      path.push_back(newpair);
      if (tryPage(nextPage, visitTable, path)) {
        hasPath = true;
      }
      path.pop_back();
    }
    visitTable[pageNum] = false;
    return hasPath;
  }

 public:
  Story() : pages(std::vector<Page>()), nowPage(0) {}

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
      // Skip the blank line.
      if (std::regex_match(strline, std::regex("\\s*"))) {
        continue;
      }
      // To check if the line is a new page.
      // Lines: number@type:filename
      if (std::regex_match(strline, std::regex("\\s*\\d+@[NLW]:.+"))) {
        size_t at_index = strline.find_first_of('@');
        size_t pageNum = myaTol(strline.c_str());
        if (pageNum != pages.size()) {
          std::cerr << "Wrong page order!\n";
          throw std::exception();
        }
        Page newPage(dirName, strline.substr(at_index + 1));
        pages.push_back(newPage);
      }
      // Lines: pagenum:destpage:text  and  pagenum[var=value]:dest:text
      else if (std::regex_match(
                   strline,
                   std::regex("\\s*\\d+(\\[[^=]*=\\s*-?\\d+\\])?:\\s*\\d+:.*"))) {
        size_t equal = 0;
        std::string condition;
        // Lines: pagenum[var=value]:dest:text
        if (std::regex_match(strline,
                             std::regex("\\s*\\d+\\[[^=]*=\\s*-?\\d+\\]:\\s*\\d+:.*"))) {
          equal = strline.find_first_of('=');
          size_t leftB = strline.find_first_of('[');
          size_t rightB = strline.find_first_of(']', equal + 1);
          condition = strline.substr(leftB + 1, rightB - leftB - 1);
        }
        size_t first = strline.find_first_of(':', equal + 1);
        size_t second = strline.find_first_of(':', first + 1);
        size_t pageNum = myaTol(strline.c_str());
        size_t destPageNum = myaTol(strline.substr(first + 1).c_str());
        // To check the choice is allowed
        if (pageNum >= pages.size()) {
          std::cerr << "Invalid page operation!\n";
          throw std::exception();
        }
        pages[pageNum].addChoice(destPageNum, strline.substr(second + 1), condition);
      }
      // Lines: pagenum$var=value
      else if (std::regex_match(strline, std::regex("\\s*\\d+\\$[^=]*=\\s*-?\\d+"))) {
        size_t dollar = strline.find_first_of('$');
        size_t pageNum = myaTol(strline.c_str());
        if (pageNum >= pages.size()) {
          std::cerr << "Invalid page operation!\n";
          throw std::exception();
        }
        pages[pageNum].addVar(strline.substr(dollar + 1));
      }
      else {
        std::cerr << "Invalid input line!\n";
        throw std::exception();
      }
    }
    free(line);
    fclose(f);
  }

  // To check if every page referenced by a choice is valid and every page has been referenced.
  void verifyTheStory() {
    size_t max = pages.size();
    std::vector<bool> refTable;
    for (size_t i = 0; i < max; i++) {
      refTable.push_back(false);
    }
    for (size_t i = 0; i < max; i++) {
      pages[i].verifyThePage(max, refTable);
    }
    for (size_t i = 1; i < max; i++) {
      if (refTable[i] == false) {
        std::cerr << "Page " << i << " has not been referenced!\n";
        throw std::exception();
      }
    }
  }

  bool readStory(const std::string & userInput) {
    if (userInput == "&&&") {
      variables = std::map<std::string, long int>();
      pages[nowPage].updateVar(variables);
      if (pages[nowPage].readPage(std::cout, variables, true)) {
        return true;
      }
      return false;
    }
    size_t userChoice = myaTol(userInput, true);
    // If the input is invalid, wait for next input.
    if (userChoice > pages[nowPage].getSize() || userChoice == 0) {
      std::cout << "That is not a valid choice, please try again\n";
      return false;
    }
    size_t nextPage = pages[nowPage].getNext(userChoice, variables);
    // If the user attempts to select an unavailable option.
    if (nextPage + 1 == 0) {
      std::cout << "That choice is not available at this time, please try again\n";
      return false;
    }
    // Update the page and then print.
    nowPage = nextPage;
    pages[nowPage].updateVar(variables);
    if (pages[nowPage].readPage(std::cout, variables, true)) {
      return true;
    }
    return false;
  }

  // Try to find paths which can win the game.
  void winTheStory() {
    std::vector<bool> visitTable;
    std::vector<std::pair<size_t, size_t> > path;
    for (size_t i = 0; i < pages.size(); i++) {
      visitTable.push_back(false);
    }
    if (!tryPage(0, visitTable, path)) {
      std::cout << "This story is unwinnable!\n";
    }
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
