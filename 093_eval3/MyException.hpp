#ifndef __MYEXCEPTION_HPP__
#define __MYEXCEPTION_HPP__

#include <exception>
#include <string>

class WrongPageOrder : public std::exception {
 public:
  virtual const char * what() const throw() { return "Wrong page order!\n"; }
};

class NoSuchFile : public std::exception {
 public:
  virtual const char * what() const throw() { return "No such file!\n"; }
};

class InvalidPageOp : public std::exception {
 public:
  virtual const char * what() const throw() { return "Invalid page operation!\n"; }
};

class InvalidInputLine : public std::exception {
 public:
  virtual const char * what() const throw() { return "Invalid input line!\n"; }
};

class InvalidStory : public std::exception {
 public:
  virtual const char * what() const throw() { return "It is not a valid story!\n"; }
};

class InvalidChoiceAdd : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "Can't add choice to a WIN/LOSS page!\n";
  }
};

class NumOutOfRange : public std::exception {
 public:
  virtual const char * what() const throw() { return "Number out of range!\n"; }
};

#endif
