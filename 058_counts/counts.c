#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  counts_t * c = malloc(sizeof(*c));
  c->arr = NULL;
  c->len = 0;
  c->unknownum = 0;
  return c;
}

void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknownum++;
    return;
  }
  for (int i = 0; i < c->len; i++) {
    if (strcmp(name, c->arr[i].stringName) == 0) {
      c->arr[i].count++;
      return;
    }
  }
  c->len++;
  c->arr = realloc(c->arr, c->len * sizeof(*c->arr));
  c->arr[c->len - 1].stringName =
      malloc((strlen(name) + 1) * sizeof(*c->arr[c->len - 1].stringName));
  strcpy(c->arr[c->len - 1].stringName, name);
  c->arr[c->len - 1].count = 1;
}
void printCounts(counts_t * c, FILE * outFile) {
  for (int i = 0; i < c->len; i++) {
    fprintf(outFile, "%s: %d\n", c->arr[i].stringName, c->arr[i].count);
  }
  if (c->unknownum > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknownum);
  }
  fclose(outFile);
}

void freeCounts(counts_t * c) {
  for (int i = 0; i < c->len; i++) {
    free(c->arr[i].stringName);
  }
  free(c->arr);
  free(c);
}
