#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList il;
    il.addFront(1);
    assert(il.head->data == 1 && il.head->next == NULL && il.head->prev == NULL);
    assert(il.tail->data == 1 && il.tail->next == NULL && il.tail->prev == NULL);
    il.addFront(2);
    assert(il.head->data == 2 && il.head->next->data == 1 && il.head->prev == NULL);
    assert(il.tail->data == 1 && il.tail->prev->data == 2 && il.tail->next == NULL);
    il.addFront(3);
    assert(il.head->data == 3 && il.head->next->prev->data == 3);
  }
  void testAddBack() {
    IntList il;
    il.addBack(1);
    assert(il.tail->data == 1 && il.tail->prev == NULL && il.tail->next == NULL);
    assert(il.head->data == 1 && il.head->prev == NULL && il.head->next == NULL);
    il.addBack(2);
    assert(il.tail->data == 2 && il.tail->prev->data == 1 && il.tail->next == NULL);
    assert(il.head->data == 1 && il.head->next->data == 2 && il.head->prev == NULL);
    il.addBack(3);
    assert(il.tail->data == 3 && il.tail->prev->next->data == 3);
  }
  void testCopyCtor() {
    IntList * il = new IntList();
    il->addFront(3);
    il->addFront(2);
    il->addFront(1);
    IntList il2(*il);
    assert(il != &il2);
    delete il;
    assert(il2.head->data == 1 && il2.head->next->data == 2 &&
           il2.head->next->next->data == 3 && il2.head->next->next->next == NULL);
    assert(il2.tail->data == 3 && il2.tail->prev->data == 2 &&
           il2.tail->prev->prev->data == 1 && il2.tail->prev->prev->prev == NULL);
    IntList il3;
    il3.addBack(100);
    il3.addBack(1000);
    il3 = il2;
    assert(&il2 != &il3);
    assert(il3.head->data == 1 && il3.head->next->data == 2 &&
           il3.head->next->next->data == 3 && il3.head->next->next->next == NULL);
    assert(il3.tail->data == 3 && il3.tail->prev->data == 2 &&
           il3.tail->prev->prev->data == 1 && il3.tail->prev->prev->prev == NULL);
  }
  void testRemove() {
    IntList il;
    assert(!il.remove(1));
    il.addFront(1);
    assert(!il.remove(2));
    assert(il.remove(1));
    assert(il.head == NULL && il.tail == NULL);
    il.addFront(1);
    il.addFront(2);
    il.remove(1);
    assert(il.head->data == 2 && il.head->next == NULL && il.tail->data == 2 &&
           il.tail->prev == NULL);
    il.addFront(1);
    il.remove(1);
    assert(il.head->data == 2 && il.head->next == NULL && il.tail->data == 2 &&
           il.tail->prev == NULL);
    il.addFront(1);
    il.addBack(3);
    il.remove(2);
    assert(il.head->data == 1 && il.head->next->data == 3 && il.head->next->next == NULL);
    assert(il.tail->data == 3 && il.tail->prev->data == 1 && il.tail->prev->prev == NULL);
  }
  // many more tester methods
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopyCtor();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
