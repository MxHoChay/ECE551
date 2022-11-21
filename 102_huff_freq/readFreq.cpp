#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <sstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  FILE * f = fopen(fname, "r");
  uint64_t * res = new uint64_t[257];
  for (size_t i = 0; i < 257; ++i) {
    res[i] = 0;
  }
  int c;
  while ((c = getc(f)) != -1) {
    ++res[(size_t)c];
  }
  if (c == -1) {
    ++res[256];
  }
  fclose(f);
  return res;
}
