#include "winograd_algo.h"

#include <regex>

namespace s21 {

void Winograd::setMatrix(const Matrix &one, const Matrix &two) {
  one_ = one;
  two_ = two;
}

Matrix Winograd::getFirstMatrix() { return one_; }

Matrix Winograd::getSecondMatrix() { return two_; }

Matrix Winograd::getResultMatrix() { return result_; }

void Winograd::matrixManualSet(int rows, int cols, char matrixNumber) {
  switch (matrixNumber) {
    case 1:
      one_ = getDataFromCin(rows, cols);
      break;
    case 2:
      two_ = getDataFromCin(rows, cols);
      break;
  }
}

std::pair<int, int> Winograd::getSizesFromCin() {
  int rows = 0, cols = 0;
  std::string bufRows, bufCols;
  std::cin >> bufRows >> bufCols;
  std::regex reg("^[0-9]+$");
  if (std::regex_match(bufRows, reg) && std::regex_match(bufCols, reg)) {
    rows = atoi(bufRows.c_str());
    cols = atoi(bufCols.c_str());
  } else {
    throw std::invalid_argument("Wrong matrix size");
  }
  checkInputSize(rows, cols);
  return {rows, cols};
}

Matrix Winograd::getDataFromCin(int rows, int cols) {
  Matrix matrix(rows, cols);
  for (int i = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getCols(); j++) {
      if (!(std::cin >> matrix(i, j))) {
        throw std::invalid_argument("Wrong matrix data");
      }
    }
  }
  return matrix;
}

void Winograd::checkInputSize(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Wrong matrix size");
  }
}

void Winograd::findRowFactor() {
  for (int i = 0; i < one_.getRows(); i++) {
    rowFactor[i] = 0;
    for (int j = 0; j < d_; j++) {
      rowFactor[i] += one_(i, 2 * j + 1) * one_(i, 2 * j);
    }
  }
}

void Winograd::findColFactor() {
  for (int i = 0; i < two_.getCols(); i++) {
    colFactor[i] = 0;
    for (int j = 0; j < d_; j++) {
      colFactor[i] += two_(2 * j + 1, i) * two_(2 * j, i);
    }
  }
}

Matrix Winograd::calculateResut() {
  Matrix result(one_.getRows(), two_.getCols());
  for (int i = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      result(i, j) = -rowFactor[i] - colFactor[j];
      for (int k = 0; k < d_; k++) {
        result(i, j) += (one_(i, 2 * k) + two_(2 * k + 1, j)) *
                        (one_(i, 2 * k + 1) + two_(2 * k, j));
      }
    }
  }
  return result;
}

void Winograd::printMatrix(const Matrix &mtrx) {
  for (int i = 0; i < mtrx.getRows(); i++) {
    for (int j = 0; j < mtrx.getCols(); j++) {
      std::cout << mtrx(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

void Winograd::checkOddSize(Matrix &res) {
  if (one_.getCols() % 2 == 1) {
    for (int i = 0; i < res.getRows(); i++)
      for (int j = 0; j < res.getCols(); j++)
        res(i, j) += one_(i, one_.getCols() - 1) * two_(two_.getRows() - 1, j);
  }
}

void Winograd::runWinogradAlgo() {
  d_ = one_.getCols() / 2;
  rowFactor.clear();
  colFactor.clear();
  rowFactor.resize(one_.getRows());
  colFactor.resize(two_.getCols());
  findRowFactor();
  findColFactor();
  Matrix res = calculateResut();
  checkOddSize(res);
  mtx.lock();
  result_ = res;
  mtx.unlock();
}

void Winograd::runWinogradAlgoMultithread() {
  d_ = one_.getCols() / 2;
  rowFactor.clear();
  colFactor.clear();
  rowFactor.resize(one_.getRows());
  colFactor.resize(two_.getCols());
  std::thread thread_1(&s21::Winograd::findRowFactor, this);
  std::thread thread_2(&s21::Winograd::findColFactor, this);
  thread_1.join();
  thread_2.join();
  Matrix res;
  std::thread thread_3([&]() { res = s21::Winograd::calculateResut(); });
  std::thread thread_4(&s21::Winograd::checkOddSize, this, std::ref(res));
  thread_3.join();
  thread_4.join();
  result_ = res;
}

void Winograd::matrixRandomSet(int rows, int cols, char matrixNumber) {
  switch (matrixNumber) {
    case 1:
      one_ = Matrix(rows, cols);
      randomFilling(one_);
      break;
    case 2:
      two_ = Matrix(rows, cols);
      randomFilling(two_);
      break;
  }
}

void Winograd::randomFilling(Matrix &mtrx) {
  std::random_device rand_r;
  std::default_random_engine engine(rand_r());
  std::uniform_int_distribution<int> oneNum(-100, 100);
  for (int i = 0; i < mtrx.getRows(); i++) {
    for (int j = 0; j < mtrx.getCols(); j++) {
      mtrx(i, j) = oneNum(engine);
    }
  }
}

}  // namespace s21
