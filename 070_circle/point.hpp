#ifndef __POINT_CPP__
#define __POINT_CPP__

class Point {
  double x;
  double y;

 public:
  Point();
  Point(const Point & p);
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};

double mypow(double x);

#endif
