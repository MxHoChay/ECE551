#include "circle.hpp"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "point.hpp"

Circle::Circle(const Point & point, double radius) : p(Point(point)), r(radius) {
}

void Circle::move(double dx, double dy) {
  p.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double dis = p.distanceFrom(otherCircle.p);
  double r1 = r;
  double r2 = otherCircle.r;
  if (dis >= r1 + r2) {
    return 0;
  }
  if (dis + r1 <= r2) {
    return PI * mypow(r1);
  }
  if (dis + r2 <= r1) {
    return PI * mypow(r2);
  }
  double gama = acos((mypow(r1) + mypow(dis) - mypow(r2)) / (2 * dis * r1));
  double beta = acos((mypow(r2) + mypow(dis) - mypow(r1)) / (2 * dis * r2));
  return mypow(r1) * (gama - sin(gama) * cos(gama)) +
         mypow(r2) * (beta - sin(beta) * cos(beta));
}
