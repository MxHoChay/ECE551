#ifndef __CIRCLE_CPP__
#define __CIRCLE_CPP__

#include "point.hpp"

#define PI acos(-1)

class Circle {
  Point p;
  const double r;

 public:
  Circle(const Point & point, double radius);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

#endif
