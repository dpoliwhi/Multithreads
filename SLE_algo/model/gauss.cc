#include "gauss.h"

namespace s21 {

void Gauss::clearData() {
  rows_ = 0;
  cols_ = 0;
  result_.clear();
}

void Gauss::loadMatrixFromFile(const std::string &fileName) {
  std::ifstream file(fileName);
  std::string line;
  if (!file.is_open()) {
    throw std::invalid_argument("No such file!");
  } else {
    int k = 0;
    bool isOpen = true;
    int countLines = 0;
    while (getline(file, line) && isOpen) {
      if (countLines == 0) {
        isOpen = parsingSize(line);
        if (!isOpen) {
          throw std::invalid_argument("Wrong matrix size");
        } else {
          mainGaussData_ = Matrix(rows_, cols_);
        }
      } else {
        std::pair<std::vector<int>, bool> oneLine = parsingLine(line);
        isOpen = oneLine.second;
        if (isOpen) {
          for (int i = 0; i < cols_; i++) {
            mainGaussData_(k, i) = oneLine.first[i];
          }
          k++;
        } else {
          throw std::invalid_argument("Invalid data in file");
        }
      }
      countLines++;
    }
    file.close();
    if (countLines != rows_ + 1) {
      throw std::invalid_argument("Invalid data in file");
    }
  }
}

bool Gauss::parsingSize(std::string line) {
  bool isCoorectSize = true;
  std::vector<int> pairOfSizes;
  std::string::iterator iter(line.begin());
  std::string buffer;
  while (iter != line.end()) {
    if (isdigit(*iter)) {
      buffer.push_back(*iter);
      if ((iter + 1) == line.end() || (*(iter + 1) == ' ')) {
        pairOfSizes.push_back(atoi(buffer.c_str()));
        buffer.clear();
      }
      ++iter;
    } else if (*iter == ' ') {
      ++iter;
    } else {
      isCoorectSize = false;
      break;
    }
  }
  if (pairOfSizes.size() == 2 && pairOfSizes[0] > 0 && pairOfSizes[1] > 0) {
    rows_ = pairOfSizes[0];
    cols_ = pairOfSizes[1];
  } else {
    isCoorectSize = false;
  }
  return isCoorectSize;
}

std::pair<std::vector<int>, bool> Gauss::parsingLine(std::string line) {
  std::vector<int> oneLine;
  std::string buffer;
  bool isValid = true;
  std::string::iterator iter(line.begin());
  while (iter != line.end()) {
    if (isdigit(*iter) || *iter == '-') {
      buffer.push_back(*iter);
      if ((iter + 1) == line.end() || ((*(iter + 1) == ' '))) {
        oneLine.push_back(atoi(buffer.c_str()));
        buffer.clear();
      }
      ++iter;
    } else if (*iter == ' ') {
      ++iter;
    } else {
      isValid = false;
      break;
    }
  }
  if ((int)oneLine.size() != cols_) {
    isValid = false;
  }
  return {oneLine, isValid};
}

void Gauss::getSize() {
  std::string bufRows, bufCols;
  std::cin >> bufRows >> bufCols;
  std::regex reg("^[0-9]+$");
  if (std::regex_match(bufRows, reg) && std::regex_match(bufCols, reg)) {
    rows_ = atoi(bufRows.c_str());
    cols_ = atoi(bufCols.c_str());
  } else {
    throw std::invalid_argument("Wrong matrix size");
  }
  checkInputSize(rows_, cols_);
}

void Gauss::getData() {
  mainGaussData_ = Matrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (!(std::cin >> mainGaussData_(i, j))) {
        throw std::invalid_argument("Wrong matrix data");
      }
    }
  }
}

void Gauss::checkInputSize(int rows, int cols) {
  if (rows < 1 || cols < 1 || ((rows + 1) != cols)) {
    throw std::invalid_argument("Wrong matrix size");
  }
}

void Gauss::printMatrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      printf("%5.0f ", mainGaussData_(i, j));
    }
    std::cout << std::endl;
  }
}

void Gauss::usualGauss() {
  copyGaussData_ = mainGaussData_;
  for (int i = 0; i < rows_; i++) {
    for (int j = i; j < rows_; j++) {
      makeIdentityMatrix(j, copyGaussData_(j, i));
    }
    for (int k = i + 1; k < rows_; k++) {
      makeTriangularMatrix(i, k);
    }
  }
  result();
}

void Gauss::result() {
  double temp[rows_];
  for (int i = rows_ - 1; i >= 0; i--) {
    temp[i] = copyGaussData_(i, rows_);
    for (int j = i + 1; j < rows_; j++) {
      temp[i] -= copyGaussData_(i, j) * temp[j];
    }
  }
  for (int i = 0; i < cols_ - 1; i++) {
    result_.push_back(temp[i]);
  }
  checkNan();
}

void Gauss::printResult() {
  for (int i = 0; i < cols_ - 1; i++) std::cout << result_[i] << " ";
  std::cout << std::endl;
}

void Gauss::parallelGauss() {
  copyGaussData_ = mainGaussData_;
  for (int i = 0; i < rows_; i++) {
    makeParallel(i, i);
  }
  result();
}

void Gauss::makeParallel(int row, int col) {
  std::vector<std::thread> threads1;
  for (int i = row; i < rows_; i++) {
    std::thread th(&Gauss::makeIdentityMatrix, this, i, copyGaussData_(i, col));
    threads1.emplace_back(std::move(th));
  }
  for (auto &th : threads1) {
    th.join();
  }
  threads1.clear();
  for (int i = row + 1; i < rows_; i++) {
    std::thread th(&Gauss::makeTriangularMatrix, this, row, i);
    threads1.emplace_back(std::move(th));
  }
  for (auto &th : threads1) {
    th.join();
  }
}

void Gauss::makeIdentityMatrix(int row, double num) {
  for (int i = 0; i < cols_; i++) {
    copyGaussData_(row, i) /= num;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void Gauss::makeTriangularMatrix(int row, int i) {
  for (int j = 0; j < cols_; j++) {
    copyGaussData_(i, j) -= copyGaussData_(row, j);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void Gauss::checkNan() {
  for (int i = 0; i < rows_; i++) {
    if (std::isnan(result_[i])) {
      throw std::invalid_argument("Incorrect system of linear equations");
    }
  }
}

}  // namespace s21
