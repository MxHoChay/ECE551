#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void helper(int * array, size_t n, size_t correct) {
  if (maxSeq(array, n) != correct) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array[14] = {1, 1, 3, 2, 4, 5, -2147483648, 2147483647};
  helper(array, 0, 0);
  helper(array, 1, 1);
  helper(&array[0], 2, 1);
  helper(&array[1], 5, 3);
  helper(&array[6], 2, 2);
  return EXIT_SUCCESS;
}
