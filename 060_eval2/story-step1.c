#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    exitErr("Invalid input format!");
  }
  FILE * f = myopen(argv[1]);
  // Read the file line by line
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) > 0) {
    parseStory(line, NULL);
  }
  free(line);
  fclose(f);
}
