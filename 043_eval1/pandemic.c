#include "pandemic.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

country_t parseLine(char * line) {
  country_t ans;
  if (line == NULL || *line == '\0' || *line == '\n') {
    fprintf(stderr, "Invalid line!");
    exit(EXIT_FAILURE);
  }
  int i;
  for (i = 0; i < 63; i++) {
    if (*line == ',' || *line == '\0' || *line == '\n') {
      break;
    }
    ans.name[i] = *line;
    line++;
  }
  if (*line == '\n' || *line == '\0' || *line != ',') {
    fprintf(stderr, "Name error!");
    exit(EXIT_FAILURE);
  }
  ans.name[i] = '\0';
  ans.population = 0;
  line++;
  bool flag = false;
  while (*line != '\n' && *line != '\0') {
    if (*line == ' ') {
      continue;
    }
    if (*line < '0' || *line > '9') {
      fprintf(stderr, "Population error!");
      exit(EXIT_FAILURE);
    }
    int dig = *line - '0';
    flag = true;
    if (ans.population > 1844674407370955161 ||
        (ans.population == 1844674407370955161 && dig > 5)) {
      fprintf(stderr, "Population too big!");
      exit(EXIT_FAILURE);
    }
    ans.population = ans.population * 10 + dig;
    line++;
  }
  if (!flag) {
    fprintf(stderr, "No population!");
    exit(EXIT_FAILURE);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  double sum = 0;
  if (n_days < 7) {
    fprintf(stderr, "Need more data!");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < 7; i++) {
    sum += data[i];
  }
  avg[0] = sum / 7;
  for (size_t i = 7; i < n_days; i++) {
    sum = sum - data[i - 7] + data[i];
    avg[i - 6] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
