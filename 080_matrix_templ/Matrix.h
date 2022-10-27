#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}

  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> *[r]) {
    for (int i = 0; i < r; i++) {
      rows[i] = new std::vector<T>(c);
    }
  }

  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(new std::vector<T> *[numRows]) {
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(*(rhs.rows[i]));
    }
  }

  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }

  Matrix & operator=(const Matrix & rhs) {
    if (this == &rhs) {
      return *this;
    }
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new std::vector<T> *[numRows];
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(*(rhs.rows[i]));
    }
    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return *(rows[index]);
  }

  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return *(rows[index]);
  }

  bool operator==(const Matrix & rhs) const {
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

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix sum(*this);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        (*(sum.rows[i]))[j] = (*(sum.rows[i]))[j] + (*(rhs.rows[i]))[j];
      }
    }
    return sum;
  }

  friend std::ostream & operator<<(std::ostream & s, const Matrix & rhs) {
    s << "[ ";
    if (rhs.getRows() == 0) {
      s << " ]";
      return s;
    }
    for (int i = 0; i < rhs.getRows(); i++) {
      s << "{";
      for (int j = 0; j < rhs.getColumns() - 1; j++) {
        s << (*(rhs.rows[i]))[j] << ", ";
      }
      s << (*(rhs.rows[i]))[rhs.getColumns() - 1];
      if (i == rhs.getRows() - 1) {
        s << "} ]";
      }
      else {
        s << "},\n";
      }
    }
    return s;
  }
};

#endif
