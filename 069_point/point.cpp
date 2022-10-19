#include "point.hpp"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Point::Point() : x(0.0), y(0.0) {
}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return sqrt(mypow(x - p.x) + mypow(y - p.y));
}

double mypow(double x) {
  return x * x;
}
