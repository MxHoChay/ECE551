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
  std::ifstream f;
  f.open(fname, std::ifstream::in);
  uint64_t * res = (uint64_t *)malloc(257 * sizeof(*res));
  char c;
  while (!f.eof()) {
    f >> c;
    ++res[(size_t)c];
  }
  return res;
}
