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
  while (*line == " ") {
    line++;
  }
  while (*line >= '0' && *line <= '9') {
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
  if (data == NULL || n_days < 7 || avg == NULL) {
    fprintf(stderr, "calcrunningavg error!");
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
  if (data == NULL || cum == NULL || pop == 0 || n_days == 0) {
    fprintf(stderr, "calccumulative error!");
    exit(EXIT_FAILURE);
  }
  double sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    sum += data[i];
    cum[i] = sum / pop * 100000;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  if (countries == NULL || n_countries == 0 || data == NULL || n_days == 0) {
    fprintf(stderr, "printcountrywithmax error!");
    exit(EXIT_FAILURE);
  }
  unsigned max = 0;
  size_t country = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > max) {
        max = data[i][j];
        country = i;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", countries[country].name, max);
}
