#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    exitErr("Invalid input format!");
  }
  catarray_t * cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  FILE * f = myopen(argv[1]);
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) > 0) {
    parseCat(line, cats);
  }
  free(line);
  printWords(cats);
  freeCat(cats);
  fclose(f);
}
