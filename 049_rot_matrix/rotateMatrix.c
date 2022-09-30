#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid input file name!");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "No such file!");
    exit(EXIT_FAILURE);
  }
  int matrix[10][10];
  int c;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      c = fgetc(f);
      if (c == EOF || c == '\n') {
        fprintf(stderr, "Line is too short!");
        exit(EXIT_FAILURE);
      }
      matrix[j][9 - i] = c;
    }
    c = fgetc(f);
    if (c != '\n') {
      fprintf(stderr, "Line is too long!");
      exit(EXIT_FAILURE);
    }
  }
  fclose(f);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
