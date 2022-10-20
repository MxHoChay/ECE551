#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "provided.h"

//any functions you want your main to use

// Exit with the message
void exitErr(const char * message);

// Open a file and check if it exists
FILE * myOpen(const char * filename);

// Convert string to int
size_t convertToInt(char * str);

// Delete the used word from cats
void deleteFromCat(catarray_t * cats, const char * category, const char * word);

// Free the space allocated to cats
void freeCat(catarray_t * cats);

// Given a string and a char, return the substring that ends before the char.
char * findWord(char * line, char flag);

// Parse each line in story, replace the blank with proper words and print
void parseStoryLine(char * line,
                    catarray_t * cats,
                    category_t * preWord,
                    bool haveUsedWord);

// Create the story by replacing words
void createStory(FILE * f, catarray_t * cats, bool haveUsedWord);

// Parse categories and words on each line
void parseCatLine(char * line, catarray_t * cats);

// Create a catarray_t
catarray_t * createCat(FILE * f);

#endif
