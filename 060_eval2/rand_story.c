#include "rand_story.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exitErr(const char * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

FILE * myOpen(const char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    exitErr("No such file!");
  }
  return f;
}

size_t convertToInt(char * str) {
  size_t res = 0;
  if (*str == '\0') {
    return 0;
  }
  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] < '0' || str[i] > '9') {
      return 0;
    }
    res = res * 10 + str[i] - '0';
  }
  return res;
}

const char * myChooseWord(char * category,
                          catarray_t * cats,
                          category_t * preWord,
                          bool flag) {
  if (!flag) {
    return chooseWord(category, cats);
  }
  bool isNewWord = false;
  const char * word = NULL;
  // To prevent looping infinitely
  size_t sum = 0;
  while (sum < 100000) {
    sum++;
    word = chooseWord(category, cats);
    isNewWord = true;
    // Make sure the new word has not been used
    for (size_t i = 0; i < preWord->n_words; i++) {
      if (strcmp(word, preWord->words[i]) == 0) {
        isNewWord = false;
        break;
      }
    }
    if (isNewWord) {
      return word;
    }
  }
  if (sum == 100000) {
    exitErr("Maybe we cannot find a unused word!");
  }
  return "NoSuchWord";
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

char * getWord(char ** line, char flag) {
  char * word = NULL;
  size_t len = 0;
  // Read the line until we find the flag
  while (**line != flag) {
    if (**line == '\0' || **line == '\n') {
      // There is no target in this line
      exitErr("Parse line error!");
    }
    word = realloc(word, ++len * sizeof(*word));
    word[len - 1] = **line;
    (*line)++;
  }
  // Add a '\0' to the tail
  word = realloc(word, (len + 1) * sizeof(*word));
  word[len] = '\0';
  (*line)++;
  return word;
}

void parseStoryLine(char * line, catarray_t * cats, category_t * preWord, bool flag) {
  // Scan the line from the begin to the end
  while (*line != '\0') {
    // Check if there is a blank
    if (*line == '_') {
      line++;
      // Get the word between '_'
      char * category = getWord(&line, '_');
      size_t index = convertToInt(category);
      const char * word = NULL;
      // Make sure the integer is a valid one
      if (index > 0 && index <= preWord->n_words) {
        word = preWord->words[preWord->n_words - index];
      }
      else {
        word = myChooseWord(category, cats, preWord, flag);
      }
      preWord->words =
          realloc(preWord->words, ++(preWord->n_words) * sizeof(*(preWord->words)));
      preWord->words[preWord->n_words - 1] =
          malloc((strlen(word) + 1) * sizeof(*(preWord->words[preWord->n_words - 1])));
      strcpy(preWord->words[preWord->n_words - 1], word);
      // Replace the blank with words and print
      printf("%s", word);
      free(category);
    }
    else {
      // Normal parts of the story
      printf("%c", *line);
      line++;
    }
  }
}

void createStory(FILE * f, catarray_t * cats, bool flag) {
  category_t * preWord = malloc(sizeof(*preWord));
  preWord->name = NULL;
  preWord->words = NULL;
  preWord->n_words = 0;
  char * line = NULL;
  size_t sz = 0;
  // Read each line of the story
  while (getline(&line, &sz, f) > 0) {
    parseStoryLine(line, cats, preWord, flag);
  }
  for (size_t i = 0; i < preWord->n_words; i++) {
    free(preWord->words[i]);
  }
  free(preWord->words);
  free(preWord);
  free(line);
}

void parseCatLine(char * line, catarray_t * cats) {
  char * category = getWord(&line, ':');
  char * word = getWord(&line, '\n');
  for (size_t i = 0; i < cats->n; i++) {
    // Check if there already exist the category
    if (strcmp(category, cats->arr[i].name) == 0) {
      bool flag = true;
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        // Make sure there is no word repeated
        if (strcmp(word, cats->arr[i].words[j]) == 0) {
          flag = false;
          break;
        }
      }
      if (flag) {
        // Add the word to the words's list
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
  // The category does not appear in the given cats, so add it.
  cats->arr = realloc(cats->arr, ++(cats->n) * sizeof(*(cats->arr)));
  cats->arr[cats->n - 1].name = category;
  cats->arr[cats->n - 1].n_words = 1;
  cats->arr[cats->n - 1].words = malloc(sizeof(*(cats->arr[cats->n - 1].words)));
  cats->arr[cats->n - 1].words[0] = word;
}

catarray_t * createCat(FILE * f) {
  catarray_t * cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) > 0) {
    parseCatLine(line, cats);
  }
  free(line);
  return cats;
}
