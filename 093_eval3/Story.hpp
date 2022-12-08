#ifndef __STORY_HPP__
#define __STORY_HPP__

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "MyException.hpp"
#include "Page.hpp"
#include "Tool.hpp"

/**
 * This class is the whole story.
 * A story consists of multiple pages.
 * This class can parse the information in story.txt and make it a final story.
 */

class Story {
  std::vector<Page> pages;
  size_t nowPage;
  std::map<std::string, long int> variables;

  /**
   * Try to make a choice and enter that page.
   * Use DFS to implement this step.
   * parameters: pageNum: the page entered this step; 
                 visitTable: to record pages that have been visited;
		 path: record the path
     return value: indicate if there is a path or not
   */
  bool tryPage(size_t pageNum,
               std::vector<bool> & visitTable,
               std::vector<std::pair<size_t, size_t> > & path) {
    // Avoid the visited page.
    if (visitTable[pageNum]) {
      return false;
    }
    // If reach the WIN page, then print the path out.
    if (pages[pageNum].isWin()) {
      for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i].first << "(" << path[i].second << "),";
      }
      std::cout << pageNum << "(win)\n";
      return true;
    }
    // If reach the LOSE page, the return false.
    else if (pages[pageNum].isLose()) {
      return false;
    }
    // Read this page and try the next one.
    visitTable[pageNum] = true;
    bool hasPath = false;
    std::set<size_t> pageset;
    // Try each choice in this page and enter the page.
    for (size_t i = 0; i < pages[pageNum].getSize(); i++) {
      size_t nextPage = pages[pageNum].getNext(i + 1, variables);
      // To avoid entering the same page.
      if (pageset.find(nextPage) == pageset.end()) {
        pageset.insert(nextPage);
      }
      else {
        continue;
      }
      // Record the path.
      std::pair<size_t, size_t> newpair(pageNum, i + 1);
      path.push_back(newpair);
      // Recursion
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

  /**
   * Construct the whole story by reading each line of story.txt
   * parameter: dirName: the path of the directory of the story.
   */
  void parseStory(const std::string & dirName) {
    FILE * f = fopen((dirName + "story.txt").c_str(), "r");
    if (f == NULL) {
      throw NoSuchFile();
    }
    char * line = NULL;
    size_t sz = 0;
    // Read each line of story.txt.
    while (getline(&line, &sz, f) > 0) {
      std::string strline(line);
      // Remove the newline character.
      if (strline[strline.length() - 1] == '\n') {
        strline.erase(strline.length() - 1);
      }
      // Skip the blank line.
      if (isMatch(strline, 0)) {
        continue;
      }
      // Get the pattern of the new line.
      bool isFileDefine = isMatch(strline, 1);
      bool isDestPage = isMatch(strline, 2);
      bool isPageWithCond = isMatch(strline, 3);
      bool isVarDefine = isMatch(strline, 4);
      // Lines: number@type:filename
      if (isFileDefine) {
        size_t at_index = strline.find_first_of('@');
        size_t pageNum = myaTol(strline.c_str());
        if (pageNum != pages.size()) {
          throw WrongPageOrder();
        }
        // Add the new page.
        Page newPage(dirName, strline.substr(at_index + 1));
        pages.push_back(newPage);
      }
      // Lines: pagenum:destpage:text  and  pagenum[var=value]:dest:text
      else if (isDestPage || isPageWithCond) {
        size_t equal = 0;
        std::string condition;
        // Lines: pagenum[var=value]:dest:text
        if (isPageWithCond) {
          equal = strline.find_first_of('=');
          size_t leftB = strline.find_first_of('[');
          size_t rightB = strline.find_first_of(']', equal + 1);
          condition = strline.substr(leftB + 1, rightB - leftB - 1);
        }
        // Parse the pagenum and destpage.
        size_t first = strline.find_first_of(':', equal + 1);
        size_t second = strline.find_first_of(':', first + 1);
        size_t pageNum = myaTol(strline.c_str());
        size_t destPageNum = myaTol(strline.substr(first + 1).c_str());
        // To check if the choice is allowed
        if (pageNum >= pages.size()) {
          throw InvalidPageOp();
        }
        pages[pageNum].addChoice(destPageNum, strline.substr(second + 1), condition);
      }
      // Lines: pagenum$var=value
      else if (isVarDefine) {
        size_t dollar = strline.find_first_of('$');
        size_t pageNum = myaTol(strline.c_str());
        if (pageNum >= pages.size()) {
          throw InvalidPageOp();
        }
        // Add the var-value to the page.
        pages[pageNum].addVar(strline.substr(dollar + 1));
      }
      else {
        throw InvalidInputLine();
      }
    }
    free(line);
    fclose(f);
  }

  /**
   * To check if every page referenced by a choice is valid and every page has been referenced.
   */
  void verifyTheStory() {
    size_t max = pages.size();
    // To record if every page is referenced by another one;
    std::vector<bool> refTable;
    // To record if there is at least one WIN and one LOSE page.
    std::vector<bool> winandlose;
    winandlose.push_back(false);
    winandlose.push_back(false);
    for (size_t i = 0; i < max; i++) {
      refTable.push_back(false);
    }
    // Verify each page.
    for (size_t i = 0; i < max; i++) {
      pages[i].verifyThePage(i, max, refTable, winandlose);
    }
    for (size_t i = 1; i < max; i++) {
      if (refTable[i] == false) {
        throw InvalidStory();
      }
    }
    if (!(winandlose[0] && winandlose[1])) {
      throw InvalidStory();
    }
  }

  /**
   * Read and print the story with the user's input.
   * This function is used in step2 and step4.
   * parameter: userInput: Input string from user.
   */
  bool readStory(const std::string & userInput) {
    // Print the first page.
    if (userInput == "&&&") {
      // Record the variable-value pairs when going through the whole story.
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

  /**
   * Try to find paths which can win the game.
   */
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
