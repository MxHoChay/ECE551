#include <stdio.h>
#include <stdlib.h>

typedef struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
} retire_info;

double myCalc(int nowAge, double init, retire_info info) {
  for (int i = 0; i < info.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", nowAge / 12, nowAge % 12 + 1, init);
    init += info.contribution + init * info.rate_of_return;
    nowAge++;
  }
  return init;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  initial = myCalc(startAge, initial, working);
  startAge += working.months;
  myCalc(startAge, initial, retired);
}

int main() {
  retire_info working;
  retire_info retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  retirement(327, 21345, working, retired);
}
