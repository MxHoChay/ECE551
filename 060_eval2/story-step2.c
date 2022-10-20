#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    exitErr("Invalid input format!");
  }
  FILE * f = myOpen(argv[1]);
  catarray_t * cats = createCat(f);
  printWords(cats);
  freeCat(cats);
  fclose(f);
}
