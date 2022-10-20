#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    exitErr("Invalid input format!");
  }
  FILE * fword = myOpen(argv[argc - 2]);
  FILE * fstory = myOpen(argv[argc - 1]);
  catarray_t * cats = createCat(fword);
  if (argc == 4 && strcmp(argv[1], "-n") == 0) {
    createStory(fstory, cats, true);
  }
  else {
    createStory(fstory, cats, false);
  }
  fclose(fword);
  fclose(fstory);
  freeCat(cats);
}
