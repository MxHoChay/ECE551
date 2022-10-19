#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>

#include "provided.h"

//any functions you want your main to use

void exitErr(const char * message);

FILE * myopen(const char * filename);

void freeCat(catarray_t * cats);

// Given a string and a char, return the substring that ends before the char.
char * findword(char * line, char flag);

// Parse each line in story, replace the blank with proper words and print
void parseStory(char * line, catarray_t * cats);

// Parse categories and words on each line
void parseCat(char * line, catarray_t * cats);

#endif
