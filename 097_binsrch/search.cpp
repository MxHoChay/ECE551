#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  return mySearch(f, low, high - 1);
}

int mySearch(Function<int, int> * f, int low, int high) {
  if (low >= high) {
    return low;
  }
  int mid = low + (high - low + 1) / 2;
  if (f->invoke(mid) <= 0) {
    return mySearch(f, mid, high);
  }
  else {
    return mySearch(f, low, mid - 1);
  }
}
