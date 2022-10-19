#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>

void exitErr(const char * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

void parseLine(const char * line, catarray_t * cats) {
  int i = 0;
  // Scan the line from the begin to the end
  while (line[i] != '\0') {
    // Check if there is a blank
    if (line[i] == '_') {
      char * category = NULL;
      size_t len = 0;
      i++;
      // Get the category between '_'
      while (line[i] != '_') {
        if (line[i] == '\n' || line[i] == '\0') {
          // Cannot find a matching underscore on the same line
          exitErr("No matching underscore on the same line!");
        }
        category = realloc(category, ++len * sizeof(*category));
        category[len - 1] = line[i];
        i++;
      }
      category = realloc(category, (len + 1) * sizeof(*category));
      category[len] = '\0';
      i++;
      // Replace the blank with words and print
      printf("%s", chooseWord(category, cats));
      free(category);
    }
    else {
      // Normal parts of the story
      printf("%c", line[i]);
      i++;
    }
  }
}
