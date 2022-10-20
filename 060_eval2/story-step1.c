#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    exitErr("Invalid input format!");
  }
  FILE * f = myOpen(argv[1]);
  createStory(f, NULL, true);
  fclose(f);
}
