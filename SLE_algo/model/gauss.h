#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <thread>
#include <vector>

#include "../../Matrix/s21_matrix_oop.h"

namespace s21 {

class Gauss {
 private:
  int rows_ = 0;
  int cols_ = 0;
  Matrix mainGaussData_;
  Matrix copyGaussData_;
  std::vector<double> result_;

  bool parsingSize(std::string line);
  std::pair<std::vector<int>, bool> parsingLine(std::string line);
  void checkInputSize(int rows, int cols);
  void makeParallel(int row, int col);
  void makeIdentityMatrix(int row, double num);
  void makeTriangularMatrix(int row, int i);
  void result();
  void checkNan();

 public:
  Gauss() = default;
  ~Gauss() = default;

  Matrix returnData() { return mainGaussData_; }
  int returnRows() { return rows_; }
  int returnCols() { return cols_; }
  void clearData();
  void loadMatrixFromFile(const std::string &fileName);
  void getSize();
  void getData();
  void printMatrix();
  void usualGauss();
  void parallelGauss();
  void printResult();
};
}  // namespace s21
