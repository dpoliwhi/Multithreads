#pragma once

#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "../../Matrix/s21_matrix_oop.h"

namespace s21 {

class Winograd {
 private:
  Matrix one_;
  Matrix two_;
  Matrix result_;
  std::mutex mtx;

  std::vector<double> rowFactor;
  std::vector<double> colFactor;
  int d_ = 0;

  Matrix getDataFromCin(int rows, int cols);
  void checkInputSize(int rows, int cols);
  void findRowFactor();
  void findColFactor();
  void checkOddSize(Matrix &res);
  Matrix calculateResut();
  void randomFilling(Matrix &mtrx);

 public:
  Matrix getFirstMatrix();
  Matrix getSecondMatrix();
  Matrix getResultMatrix();
  void runWinogradAlgo();
  void runWinogradAlgoMultithread();
  void printMatrix(const Matrix &mtrx);
  void matrixManualSet(int rows, int cols, char matrixNumber);
  void matrixRandomSet(int rows, int cols, char matrixNumber);
  void setMatrix(const Matrix &one, const Matrix &two);
  std::pair<int, int> getSizesFromCin();
};
}  // namespace s21
