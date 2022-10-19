#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    exitErr("Invalid input format!");
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    exitErr("No such file!");
  }
  // Read the file line by line
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) > 0) {
    parseLine(line, NULL);
  }
  free(line);
  fclose(f);
}
