#pragma once
namespace s21 {

class Matrix {
 private:
  int _rows, _cols;
  double **_matrix;

 public:
  // Constructors
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);
  // Destructor
  ~Matrix();
  // Methods
  bool eq_matrix(const Matrix &other) const;
  void sum_matrix(const Matrix &other);
  void sub_matrix(const Matrix &other);
  void mul_number(const double num);
  void mul_matrix(const Matrix &other);
  Matrix transpose() const;
  Matrix calc_complements() const;
  double determinant() const;
  Matrix inverse_matrix() const;
  // Accessors
  int getRows() const;
  int getCols() const;
  void setRows(int rows);
  void setCols(int cols);
  // Operators
  Matrix operator+(const Matrix &other) const;
  Matrix operator-(const Matrix &other) const;
  Matrix operator*(const Matrix &other) const;
  Matrix operator*(const double num) const;
  friend Matrix operator*(const double num, const Matrix &other);
  bool operator==(const Matrix &other) const;
  Matrix &operator=(const Matrix &other);
  Matrix operator+=(const Matrix &other);
  Matrix operator-=(const Matrix &other);
  Matrix operator*=(const Matrix &other);
  Matrix operator*=(const double num);
  const double &operator()(int i, int j) const;
  double &operator()(int i, int j);

  void destroyMatrix();
  // Other
 private:
  inline bool isEqualSizes(const Matrix &other) const;
  inline bool isSquareMatrix() const;
  void newMatrix(int rows, int cols);
  void copyMatrix(double **other_matrix);
  Matrix getMinor(int line, int col) const;
};

Matrix operator*(double num, const Matrix &other);

}  // namespace s21
