#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new IntArray *[numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(*(rhs.rows[i]));
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this == &rhs) {
    return *this;
  }
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(*(rhs.rows[i]));
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}

int IntMatrix::getColumns() const {
  return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *(rows[index]);
}

IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *(rows[index]);
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if (*(rows[i]) != *(rhs.rows[i])) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix sum(*this);
  for (int i = 0; i < numRows; i++) {
    *(sum.rows[i]) = *(sum.rows[i]) + *(rhs.rows[i]);
  }
  return sum;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  if (rhs.getRows() == 0) {
    s << " ]";
    return s;
  }
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }
  s << rhs[rhs.getRows() - 1] << " ]";
  return s;
}
