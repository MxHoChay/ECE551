#include <cstdlib>
#include <iostream>

#include "bstset.h"

int main(void) {
  BstSet<int> * set = new BstSet<int>();
  set->add(1);
  set->add(100);
  set->add(30);
  std::cout << set->contains(20) << std::endl;
  set->remove(20);
  set->remove(30);
  set->remove(100);
  BstSet<int> * set1 = new BstSet<int>(*set);
  BstSet<int> set2;
  set2 = *set1;
  delete set;
  std::cout << set1->contains(1) << std::endl;
  delete set1;
  std::cout << set2.contains(30) << std::endl;
  return 0;
}
