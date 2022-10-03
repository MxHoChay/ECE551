#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  char ** lines = NULL;
  char * line = NULL;
  size_t sz;
  size_t i = 0;
  if (argc == 1) {
    while (getline(&line, &sz, stdin) > 1) {
      lines = realloc(lines, (i + 1) * sizeof(*lines));
      lines[i] = line;
      line = NULL;
      i++;
    }
    free(line);
    sortData(lines, i);
    for (size_t j = 0; j < i; j++) {
      printf("%s", lines[j]);
      free(lines[j]);
    }
    free(lines);
  }
  else {
    for (int j = 1; j < argc; j++) {
      FILE * f = fopen(argv[j], "r");
      if (f == NULL) {
        fprintf(stderr, "Can't find the file!");
        exit(EXIT_FAILURE);
      }
      i = 0;
      while (getline(&line, &sz, f) >= 0) {
        lines = realloc(lines, (i + 1) * sizeof(*lines));
        lines[i] = line;
        line = NULL;
        i++;
      }
      free(line);
      line = NULL;
      if (i == 0) {
        fprintf(stderr, "No line!");
        exit(EXIT_FAILURE);
      }
      sortData(lines, i);
      for (size_t k = 0; k < i; k++) {
        printf("%s", lines[k]);
        free(lines[k]);
      }
      free(lines);
      lines = NULL;
      fclose(f);
    }
  }
  return EXIT_SUCCESS;
}
