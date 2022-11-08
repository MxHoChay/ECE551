#ifndef __BSTSET_H__
#define __BSTSET_H__

#include <cstdlib>
#include <stdexcept>

#include "bstmap.h"
#include "set.h"

template<typename T>
class BstSet : public Set<T> {
  BstMap<T, int> * set;

 public:
  BstSet<T>() : set(new BstMap<T, int>()) {}
  BstSet<T>(const BstSet & rhs) {
    delete set;
    set = new BstMap<T, int>(rhs.set);
  }
  BstSet & operator=(const BstSet & rhs) {
    if (this == &rhs) {
      return *this;
    }
    delete set;
    set = new BstMap<T, int>(rhs.set);
  }

  virtual void add(const T & key) { set->add(key, 0); }

  virtual bool contains(const T & key) {
    try {
      set->lookup(key);
    }
    catch (std::invalid_argument) {
      return false;
    }
    return true;
  }

  virtual void remove(const T & key) { set->remove(key); }

  virtual ~BstSet<T>() { delete set; }
};

#endif
