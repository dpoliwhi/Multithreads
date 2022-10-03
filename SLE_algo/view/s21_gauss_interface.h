#pragma once

#include <iostream>

#include "../../Matrix/s21_matrix_oop.h"
#include "../../SimpleTimer.h"
#include "../model/gauss.h"

namespace s21 {

class GaussInterface {
 public:
  void startProgram();
  Gauss SLE;

 private:
  void informationPart();
  void firstMenu();
  void fileReading();
  void enterData();
  void printMainData();
  void runTimer();
  void runUsualGauss(int cycles);
  void runParallelGauss(int cycles);
  void printMatrix(s21::Matrix res);
  void endMenu();
  void exitOrRestart();
  void handleIncorrectMenuChoice();
  void final();

  std::string end = "\u001b[0m";
  std::string end1 = "\u001b[0m\n";
  std::string style1 = "\u001b[1;38;5;117m";
  std::string style2 = "\u001b[1;48;5;25;38;5;117m";
  std::string style3 = "\u001b[1;48;5;117;38;5;25m";
  std::string style4 = "\u001b[1;38;5;117m";
};

}  // namespace s21
