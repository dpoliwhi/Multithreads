#include "s21_gauss_interface.h"

#include <iostream>

namespace s21 {

void GaussInterface::startProgram() {
  informationPart();
  firstMenu();
}

void GaussInterface::informationPart() {
  std::cout << style1 << "\n---------------------------------------------"
            << end << std::endl;
  std::cout << style2 << "       WELCOME TO PROGRAM TO SOLVE SLE       " << end
            << std::endl;
  std::cout << style1 << "---------------------------------------------" << end
            << std::endl;
  std::cout << style4 << "             program created  by" << end << std::endl;
  std::cout << style4 << "             dpoliwhi & esharika" << end << std::endl;
  std::cout << style1 << "---------------------------------------------" << end1
            << std::endl;
}

void GaussInterface::endMenu() {
  std::cout << style1 << "---------------------------------------------" << end
            << std::endl;
  std::cout << style2 << "              ALGORITHM COMPLITED            " << end
            << std::endl;
  std::cout << style1 << "---------------------------------------------" << end1
            << std::endl;
  std::cout << style3 << " 1. Restart program                          " << end
            << std::endl;
  std::cout << style3 << " 0. Exit from the program                    " << end1
            << std::endl;
}

void GaussInterface::firstMenu() {
  SLE.clearData();
  std::cout << style3 << " 1. Load matrix from file                    " << end
            << std::endl;
  std::cout << style3 << " 2. Enter matrix                             " << end1
            << std::endl;
  int choice;
  if (std::cin >> choice) {
    if (choice == 1) {
      fileReading();
    } else if (choice == 2) {
      enterData();
    } else {
      handleIncorrectMenuChoice();
      firstMenu();
    }
  } else {
    handleIncorrectMenuChoice();
    firstMenu();
  }
}

void GaussInterface::fileReading() {
  while (true) {
    std::cout << "\n"
              << style3 << " Please enter file name                      "
              << end << std::endl;
    std::cout << std::endl;
    std::string filename;
    std::cin >> filename;
    try {
      SLE.loadMatrixFromFile("../datasets/" + filename);
      break;
    } catch (std::exception &exceptionText) {
      std::cerr << style4 << "\nError: " << exceptionText.what() << end << "\n";
    }
  }
  runTimer();
  exitOrRestart();
}

void GaussInterface::enterData() {
  std::cout << "\n"
            << style3 << " Enter matrix size                           " << end1
            << std::endl;
  try {
    SLE.getSize();
  } catch (std::exception &exceptionText) {
    std::cerr << style4 << "\nError: " << exceptionText.what() << end << "\n\n";
    enterData();
  }
  std::cout << "\n"
            << style3 << " Enter matrix values                         " << end1
            << std::endl;
  SLE.getData();
  runTimer();
  exitOrRestart();
}

void GaussInterface::printMainData() {
  std::cout << "\n"
            << style3 << " Main Data                                   " << end1
            << std::endl;
  SLE.printMatrix();
  std::cout << "\n" << end;
}

void GaussInterface::runTimer() {
  printMainData();
  int cycles;
  std::cout << "\n"
            << style3 << " Enter number of cycles                      " << end1
            << std::endl;
  if (std::cin >> cycles) {
    try {
      Simpletimer timer;
      timer.startTime();
      if (cycles > 0) {
        runUsualGauss(cycles);
      }
      std::cout << "\nRuntime usual = " << timer.getTime() << std::endl;
      timer.startTime();
      if (cycles > 0) {
        runParallelGauss(cycles);
      }
      std::cout << "\nRuntime parallel = " << timer.getTime() << std::endl;
    } catch (std::exception &exceptionText) {
      std::cerr << style4 << "\nError: " << exceptionText.what() << end << "\n";
    }
  } else {
    handleIncorrectMenuChoice();
    runTimer();
  }
}

void GaussInterface::runUsualGauss(int cycles) {
  for (int i = 0; i < cycles; i++) {
    SLE.usualGauss();
    if (i == 0) {
      std::cout << "\n"
                << style3
                << " Usual Gauss Answer:                         " << end1
                << std::endl;
      SLE.printResult();
    }
  }
}

void GaussInterface::runParallelGauss(int cycles) {
  for (int i = 0; i < cycles; i++) {
    SLE.parallelGauss();
    if (i == 0) {
      std::cout << "\n"
                << style3
                << " Parallel Gauss Answer:                         " << end1
                << std::endl;
      SLE.printResult();
    }
  }
}

void GaussInterface::exitOrRestart() {
  endMenu();
  int choice;
  if (std::cin >> choice) {
    if (choice == 1) {
      std::cout << "\n";
      firstMenu();
    } else if (choice == 0) {
      return;
    } else {
      handleIncorrectMenuChoice();
      exitOrRestart();
    }
  } else {
    handleIncorrectMenuChoice();
    exitOrRestart();
  }
}

void GaussInterface::handleIncorrectMenuChoice() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << style4 << "\nError: incorrect input, try again " << end1
            << std::endl;
}

}  // namespace s21
