#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() {
  numElements = 0;
  data = NULL;
}
IntArray::IntArray(int n) {
  numElements = n;
  data = (int *)malloc(n * sizeof(*data));
}

IntArray::IntArray(const IntArray & rhs) {
  numElements = rhs.numElements;
  data = (int *)malloc(numElements * sizeof(*data));
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  free(data);
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  numElements = rhs.numElements;
  data = (int *)realloc(data, numElements * sizeof(*data));
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index < numElements);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index >= 0 && index < numElements);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.numElements <= 0) {
    return s;
  }
  s << "{" << rhs.data[0];
  for (int i = 1; i < rhs.numElements; i++) {
    s << "," << rhs.data[i];
  }
  s << "}" << std::endl;
  return s;
}
