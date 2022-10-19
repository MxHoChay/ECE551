#include "rand_story.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exitErr(const char * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

FILE * myopen(const char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    exitErr("No such file!");
  }
  return f;
}

void freeCat(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].name);
    free(cats->arr[i].words);
  }
  free(cats->arr);
  free(cats);
}

char * getword(char ** line, char flag) {
  char * word = NULL;
  size_t len = 0;
  while (**line != flag) {
    if (**line == '\0' || **line == '\n') {
      // There is no target in this line
      exitErr("Parse line error!");
    }
    word = realloc(word, ++len * sizeof(*word));
    word[len - 1] = **line;
    (*line)++;
  }
  word = realloc(word, (len + 1) * sizeof(*word));
  word[len] = '\0';
  (*line)++;
  return word;
}

void parseStory(char * line, catarray_t * cats) {
  // Scan the line from the begin to the end
  while (*line != '\0') {
    // Check if there is a blank
    if (*line == '_') {
      line++;
      // Get the word between '_'
      char * category = getword(&line, '_');
      // Replace the blank with words and print
      printf("%s", chooseWord(category, cats));
      free(category);
    }
    else {
      // Normal parts of the story
      printf("%c", *line);
      line++;
    }
  }
}

void parseCat(char * line, catarray_t * cats) {
  char * category = getword(&line, ':');
  char * word = getword(&line, '\n');
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(category, cats->arr[i].name) == 0) {
      bool flag = true;
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        if (strcmp(word, cats->arr[i].words[j]) == 0) {
          flag = false;
          break;
        }
      }
      if (flag) {
        cats->arr[i].words = realloc(
            cats->arr[i].words, ++(cats->arr[i].n_words) * sizeof(*(cats->arr[i].words)));
        cats->arr[i].words[cats->arr[i].n_words - 1] = word;
      }
      else {
        free(word);
      }
      free(category);
      return;
    }
  }
  cats->arr = realloc(cats->arr, ++(cats->n) * sizeof(*(cats->arr)));
  cats->arr[cats->n - 1].name = category;
  cats->arr[cats->n - 1].n_words = 1;
  cats->arr[cats->n - 1].words = malloc(sizeof(*(cats->arr[cats->n - 1].words)));
  cats->arr[cats->n - 1].words[0] = word;
}
