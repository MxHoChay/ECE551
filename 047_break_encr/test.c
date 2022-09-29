#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void findKey(FILE * f) {
  int c;
  int table[26] = {0};
  int max = 0;
  int maxc = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      table[c - 'a']++;
      if (table[c - 'a'] > max) {
        maxc = c;
        max = table[c - 'a'];
      }
    }
  }
  for (int i = 0; i < 26; i++) {
    if (table[i] == max && 'a' + i != maxc) {
      fprintf(stderr, "More than one \"e\"!\n");
      exit(EXIT_FAILURE);
    }
  }
  printf("%d\n", (maxc - 'e' + 26) % 26);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid input file name!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "No such file!\n");
    exit(EXIT_FAILURE);
  }
  findKey(f);
  return EXIT_SUCCESS;
}
