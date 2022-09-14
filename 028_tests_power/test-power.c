#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned ans) {
  if (power(x, y) != ans) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(0, 1, 0);
  run_check(2, 3, 8);
  run_check(32768, 1, 32768);
  run_check(-1, 0, 1);
  run_check(-1, 1, -1);
  return EXIT_SUCCESS;
}
