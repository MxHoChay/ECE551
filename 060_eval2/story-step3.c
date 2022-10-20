#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    exitErr("Invalid input format!");
  }
  FILE * fcat = myOpen(argv[1]);
  FILE * fstory = myOpen(argv[2]);

  // Create cats from input
  catarray_t * cats = createCat(fcat);

  // Create the story in fstory
  createStory(fstory, cats, true);

  fclose(fcat);
  fclose(fstory);
  freeCat(cats);
}
