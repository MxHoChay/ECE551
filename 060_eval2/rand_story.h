#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

void exitErr(const char * message);

// Parse each line, replace the blank with proper words and print
void parseLine(const char * line, catarray_t * cats);

#endif
