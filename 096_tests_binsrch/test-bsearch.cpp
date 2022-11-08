#include <math.h>
#include <stdio.h>

#include <cstdlib>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}

  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

  virtual ~CountedIntFn() {}
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int max = 1;
  if (high > low) {
    max = log2(high - low) + 1;
  }
  CountedIntFn fn(max, f, mesg);
  int ans = binarySearchForZero(&fn, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "Incorrect answer in %s %d\n", mesg, ans);
    exit(EXIT_FAILURE);
  }
}

class myFunc : public Function<int, int> {
 private:
  int k;
  int b;

 public:
  myFunc(int _k, int _b) : k(_k), b(_b) {}
  virtual int invoke(int arg) { return k * arg + b; }
  virtual ~myFunc() {}
};

int main(void) {
  myFunc f(1, 0);
  myFunc f1(4, -2);
  myFunc f2(0, -1);
  check(&f, -1000, 1000, 0, "x");
  check(&f, -1000, 0, -1, "x");
  check(&f, 0, 0, 0, "x");
  check(&f, 10, 1000, 10, "x");
  check(&f1, -1000, 1000, 0, "2x-1");
  check(&f2, -100, 100, 99, "-1");
  myFunc f3(2, 2);
  check(&f3, -100, 100, -1, "-x");
}
