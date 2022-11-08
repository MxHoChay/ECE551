#include <cstdlib>
#include <iostream>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> map;
  map.add(33, 2);
  map.add(44, 1);
  map.add(12, 1);
  map.add(55, 1);
  map.add(99, 3);
  map.add(16, 0);
  map.add(77, 0);
  map.add(0, 0);
  map.add(-1, 0);
  map.add(100, 0);

  std::cout << map.lookup(-1) << std::endl;
  map.remove(33);
  map.remove(12);
}
