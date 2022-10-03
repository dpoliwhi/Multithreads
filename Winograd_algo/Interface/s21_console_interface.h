#pragma once

#include <stdio.h>

#include <algorithm>
#include <iostream>

#include "../../SimpleTimer.h"
#include "../Model/winograd_algo.h"

namespace s21 {

class ConsoleInterface {
 public:
  void startProgram();

 private:
  Winograd win;
  std::pair<int, int> sizeFirst;
  std::pair<int, int> sizeSecond;

  void informationPart();
  void createMatrix();
  void inputMenu();
  void setDataManual(int choiceMtrx);
  void handleIncorrectSizes();
  void handleIncorrectMenuChoice();
  void menuText();
  void exitOrRestart();
  void endMenu();
  void printAndRunMenu();
  void runAlgorithm();
  void runClassicalParallelism(int n);
  void printMenu();
  void printMatrix(s21::Matrix mtrx, const std::string &choiceMtrx);

  std::string end = "\u001b[0m";
  std::string end1 = "\u001b[0m\n";
  std::string style1 = "\u001b[1;38;5;117m";
  std::string style2 = "\u001b[1;48;5;25;38;5;117m";
  std::string style3 = "\u001b[1;48;5;117;38;5;25m";
  std::string style4 = "\u001b[1;38;5;117m";
};

}  // namespace s21
