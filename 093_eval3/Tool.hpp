#ifndef __TOOL_HPP__
#define __TOOL_HPP__

#include <iostream>
#include <string>

bool isNum(const std::string & str, size_t & i, bool hasSign = false) {
  while (i < str.length() && str[i] == ' ') {
    ++i;
  }
  if (hasSign) {
    if (i == str.length()) {
      return false;
    }
    if (str[i] == '-') {
      ++i;
    }
  }
  if (i == str.length() || str[i] < '0' || str[i] > '9') {
    return false;
  }
  while (i < str.length() && str[i] >= '0' && str[i] <= '9') {
    ++i;
  }
  return true;
}

bool isMatch(const std::string & str, int pattern) {
  size_t i = 0;
  size_t len = str.length();
  if (pattern == 0) {
    while (i < len && str[i] == ' ') {
      ++i;
    }
    if (i < len) {
      return false;
    }
  }
  // number@type:filename \\s*\\d+@[NLW]:.+
  else if (pattern == 1) {
    if (!isNum(str, i)) {
      return false;
    }
    if (i == len || str[i] != '@') {
      return false;
    }
    ++i;
    if (i == len || (str[i] != 'N' && str[i] != 'L' && str[i] != 'W')) {
      return false;
    }
    ++i;
    if (i == len || str[i] != ':') {
      return false;
    }
    ++i;
    if (i == len) {
      return false;
    }
  }
  // pagenum:destpage:text  and  pagenum[var=value]:dest:text
  else if (pattern == 2 || pattern == 3) {
    if (!isNum(str, i)) {
      return false;
    }
    if (pattern == 3) {
      if (i == len || str[i] != '[') {
        return false;
      }
      ++i;
      while (i < len && str[i] != '=') {
        ++i;
      }
      if (i == len) {
        return false;
      }
      ++i;
      if (!isNum(str, i, true)) {
        return false;
      }
      if (i == len || str[i] != ']') {
        return false;
      }
      ++i;
    }
    if (i == len || str[i] != ':') {
      return false;
    }
    ++i;
    if (!isNum(str, i)) {
      return false;
    }
    if (i == len || str[i] != ':') {
      return false;
    }
  }
  // pagenum$var=value
  else if (pattern == 4) {
    if (!isNum(str, i)) {
      return false;
    }
    if (i == len || str[i] != '$') {
      return false;
    }
    ++i;
    while (i < len && str[i] != '=') {
      ++i;
    }
    if (i == len) {
      return false;
    }
    ++i;
    if (!isNum(str, i, true)) {
      return false;
    }
    if (i < len) {
      return false;
    }
  }
  return true;
}

// Convert string to size_t.
size_t myaTol(const std::string & str, bool isUser = false) {
  size_t i = 0;
  size_t len = str.length();
  if (isUser && (!isNum(str, i) || i != len)) {
    return 0;
  }
  else {
    size_t res = std::strtoul(str.c_str(), NULL, 10);
    if (errno != 0) {
      std::cerr << "Invalid number!\n";
      throw std::exception();
    }
    return res;
  }
}

#endif
