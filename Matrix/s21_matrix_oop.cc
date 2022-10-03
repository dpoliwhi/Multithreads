#include "s21_matrix_oop.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace s21 {
// Constructors
Matrix::Matrix() { newMatrix(1, 1); }

Matrix::Matrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    newMatrix(rows, cols);
  } else {
    throw std::out_of_range(
        "Incorrect input, matrix should have both sizes > 0");
  }
}

Matrix::Matrix(const Matrix &other) : Matrix(other._rows, other._cols) {
  copyMatrix(other._matrix);
}

Matrix::Matrix(Matrix &&other) {
  _rows = other._rows;
  _cols = other._cols;
  _matrix = other._matrix;
  other._matrix = nullptr;
}

// Destructor
Matrix::~Matrix() {
  if (_matrix) {
    destroyMatrix();
  }
}

// Methods
bool Matrix::eq_matrix(const Matrix &other) const {
  bool result = true;
  if (isEqualSizes(other)) {
    for (int i = 0; i < _rows && result; i++) {
      for (int j = 0; j < _cols && result; j++) {
        if (fabs(_matrix[i][j] - other._matrix[i][j]) > 1e-7) result = false;
      }
    }
  } else {
    result = false;
  }
  return result;
}

void Matrix::sum_matrix(const Matrix &other) {
  if (isEqualSizes(other)) {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _cols; j++) {
        _matrix[i][j] = _matrix[i][j] + other._matrix[i][j];
      }
    }
  } else {
    throw std::invalid_argument(
        "Invalid argument, matrices must be equal sizes");
  }
}

void Matrix::sub_matrix(const Matrix &other) {
  if (isEqualSizes(other)) {
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _cols; j++) {
        _matrix[i][j] = _matrix[i][j] - other._matrix[i][j];
      }
    }
  } else {
    throw std::invalid_argument(
        "Invalid argument, matrices must be equal sizes");
  }
}

void Matrix::mul_number(const double num) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] *= num;
    }
  }
}

void Matrix::mul_matrix(const Matrix &other) {
  if (_cols == other._rows) {
    Matrix result(_rows, other._cols);
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < other._cols; j++) {
        for (int c = 0; c < _cols; c++)
          result._matrix[i][j] += _matrix[i][c] * other._matrix[c][j];
      }
    }
    *this = result;
  } else {
    throw std::invalid_argument(
        "Invalid argument, number of cols of the first matrix must be equal to "
        "number of rows of the "
        "second matrix");
  }
}

Matrix Matrix::transpose() const {
  Matrix result(_cols, _rows);
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) result._matrix[j][i] = _matrix[i][j];
  return result;
}

double Matrix::determinant() const {
  if (isSquareMatrix()) {
    double result = _matrix[0][0];
    if (_rows > 1 && _cols > 1) {
      result = 0.0;
      for (int j = 0; j < _cols; j++) {
        Matrix minor = getMinor(0, j);
        if (j % 2 == 0)
          result += _matrix[0][j] * minor.determinant();
        else
          result -= _matrix[0][j] * minor.determinant();
      }
    }
    return result;
  } else {
    throw std::invalid_argument("Invalid argument, matrix must be square");
  }
}

Matrix Matrix::calc_complements() const {
  if (isSquareMatrix() && _rows > 1) {
    Matrix result(_rows, _cols);
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _cols; j++) {
        Matrix minor = getMinor(i, j);
        if ((i + j) % 2 == 0) {
          result._matrix[i][j] = minor.determinant();
        } else {
          result._matrix[i][j] = -minor.determinant();
        }
      }
    }
    return result;
  } else {
    throw std::invalid_argument(
        "Invalid argument, matrix must be square and > 1 size");
  }
}

Matrix Matrix::inverse_matrix() const {
  if (fabs(determinant()) > 1e-7) {
    Matrix result(1, 1);
    if (_rows > 1) {
      Matrix complem = calc_complements();
      Matrix buffer = complem.transpose();
      buffer.mul_number(1.0 / determinant());
      result = buffer;
    } else {
      result._matrix[0][0] = 1.0 / _matrix[0][0];
    }
    return result;
  } else {
    throw std::invalid_argument(
        "Invalid argument, matrix determinant equals zero");
  }
}

// Accessors
int Matrix::getRows() const { return _rows; }

int Matrix::getCols() const { return _cols; }

void Matrix::setRows(int rows) { _rows = rows; }

void Matrix::setCols(int cols) { _cols = cols; }

// Operators
Matrix Matrix::operator+(const Matrix &other) const {
  Matrix result = *this;
  result.sum_matrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
  Matrix result = *this;
  result.sub_matrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
  Matrix result = *this;
  result.mul_matrix(other);
  return result;
}

Matrix Matrix::operator*(const double num) const {
  Matrix result = *this;
  result.mul_number(num);
  return result;
}

Matrix operator*(double num, const Matrix &other) {
  Matrix result = other;
  result.mul_number(num);
  return result;
}

bool Matrix::operator==(const Matrix &other) const { return eq_matrix(other); }

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    destroyMatrix();
    newMatrix(other._rows, other._cols);
    copyMatrix(other._matrix);
  }
  return *this;
}

Matrix Matrix::operator+=(const Matrix &other) {
  sum_matrix(other);
  return *this;
}

Matrix Matrix::operator-=(const Matrix &other) {
  sub_matrix(other);
  return *this;
}

Matrix Matrix::operator*=(const Matrix &other) {
  mul_matrix(other);
  return *this;
}

Matrix Matrix::operator*=(const double num) {
  mul_number(num);
  return *this;
}

const double &Matrix::operator()(int i, int j) const {
  if (i >= 0 && i < _rows && j >= 0 && j < _cols) {
    return _matrix[i][j];
  } else {
    throw std::out_of_range("Incorrect input, index out of matrix sizes");
  }
}

double &Matrix::operator()(int i, int j) {
  if (i >= 0 && i < _rows && j >= 0 && j < _cols) {
    return _matrix[i][j];
  } else {
    throw std::out_of_range("Incorrect input, index out of matrix sizes");
  }
}

// Other
inline bool Matrix::isEqualSizes(const Matrix &other) const {
  return (_rows == other._rows && _cols == other._cols);
}

inline bool Matrix::isSquareMatrix() const { return (_rows == _cols); }

void Matrix::newMatrix(int rows, int cols) {
  _rows = rows;
  _cols = cols;
  _matrix = new double *[_rows];
  for (int i = 0; i < _rows; i++) {
    _matrix[i] = new double[_cols]();
  }
}

void Matrix::destroyMatrix() {
  for (int i = 0; i < _rows; i++) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

void Matrix::copyMatrix(double **other_matrix) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] = other_matrix[i][j];
    }
  }
}

Matrix Matrix::getMinor(int line, int col) const {
  Matrix minor(_rows - 1, _cols - 1);
  int l = 0;
  for (int i = 0; i < _rows; i++) {
    int c = 0;
    for (int j = 0; j < _cols && i != line; j++) {
      if (j != col) {
        minor._matrix[l][c] = _matrix[i][j];
        c++;
      }
    }
    if (i != line) l++;
  }
  return minor;
}
}  // namespace s21
