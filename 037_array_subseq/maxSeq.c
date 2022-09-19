#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n <= 1) {
    return n;
  }
  size_t res = 1;
  size_t len = 1;
  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      len++;
      res = len > res ? len : res;
    }
    else {
      len = 1;
    }
  }
  return res;
}
