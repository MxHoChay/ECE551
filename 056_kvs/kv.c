#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Invalid file name!");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kvarr = malloc(sizeof(*kvarr));
  kvarr->arr = NULL;
  kvarr->len = 0;
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) > 0) {
    if (*line == '\n') {
      continue;
    }
    kvarr->len++;
    kvarr->arr = realloc(kvarr->arr, kvarr->len * sizeof(*kvarr->arr));
    myReadLine(line, &kvarr->arr[kvarr->len - 1]);
  }
  fclose(f);
  free(line);
  return kvarr;
}

void myReadLine(char * line, kvpair_t * kvtarget) {
  kvtarget->key = NULL;
  kvtarget->value = NULL;
  readKeyorVal(&line, &kvtarget->key, '=');
  readKeyorVal(&line, &kvtarget->value, '\n');
}

void readKeyorVal(char ** line, char ** target, char sign) {
  int len = 0;
  while (**line != sign) {
    *target = realloc(*target, ++len * sizeof(**target));
    (*target)[len - 1] = **line;
    (*line)++;
  }
  *target = realloc(*target, ++len * sizeof(*target));
  (*target)[len - 1] = '\0';
  (*line)++;
}

void freeKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->len; i++) {
    free(pairs->arr[i].key);
    free(pairs->arr[i].value);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->len; i++) {
    printf("key = '%s' value = '%s'\n", pairs->arr[i].key, pairs->arr[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (int i = 0; i < pairs->len; i++) {
    if (strcmp(pairs->arr[i].key, key) == 0) {
      return pairs->arr[i].value;
    }
  }
  return NULL;
}
