#include "pandemic.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

country_t parseLine(char * line) {
  country_t ans;
  // To make sure the line is readable.
  if (line == NULL) {
    fprintf(stderr, "Invalid line!");
    exit(EXIT_FAILURE);
  }
  if (*line == '\0' || *line == '\n') {
    exit(EXIT_SUCCESS);
  }
  int i;
  for (i = 0; i < 63; i++) {
    if (*line == ',' || *line == '\0' || *line == '\n') {
      break;
    }
    ans.name[i] = *line;
    line++;
  }
  // If the country name is not followed by a comma, then exit with failure.
  if (*line == '\n' || *line == '\0' || *line != ',') {
    fprintf(stderr, "Name error!");
    exit(EXIT_FAILURE);
  }
  ans.name[i] = '\0';
  ans.population = 0;
  line++;
  bool flag = false;
  // Clear all the spaces in front of the number.
  while (*line == ' ') {
    line++;
  }
  while (*line != '\0' && *line != '\n') {
    if (*line < '0' || *line > '9') {
      fprintf(stderr, "Population error!");
      exit(EXIT_FAILURE);
    }
    int dig = *line - '0';
    flag = true;
    // Make sure the population do not exceed uint64.
    if (ans.population > 1844674407370955161 ||
        (ans.population == 1844674407370955161 && dig > 5)) {
      fprintf(stderr, "Population too big!");
      exit(EXIT_FAILURE);
    }
    ans.population = ans.population * 10 + dig;
    line++;
  }
  // No number is detected.
  if (!flag) {
    fprintf(stderr, "No population!");
    exit(EXIT_FAILURE);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  double sum = 0;
  if (data == NULL || avg == NULL) {
    fprintf(stderr, "calcrunningavg error!");
    exit(EXIT_FAILURE);
  }
  if (n_days < 7) {
    exit(EXIT_SUCCESS);
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
  if (data == NULL || cum == NULL || pop == 0) {
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
  if (countries == NULL || data == NULL || n_countries == 0 || n_days == 0) {
    fprintf(stderr, "printcountrywithmax error!");
    exit(EXIT_FAILURE);
  }
  unsigned max = 0;
  size_t max_country = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > max) {
        max = data[i][j];
        max_country = i;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", countries[max_country].name, max);
}
