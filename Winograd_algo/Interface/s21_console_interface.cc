#include "s21_console_interface.h"

namespace s21 {

void ConsoleInterface::startProgram() {
  informationPart();
  createMatrix();
  handleIncorrectSizes();
  inputMenu();
}

void ConsoleInterface::createMatrix() {
  while (true) {
    std::cout << style3 << " please enter size of 1-st matrix            "
              << end1 << std::endl;
    try {
      sizeFirst = win.getSizesFromCin();
      std::cout << std::endl;
      break;
    } catch (std::exception &exceptionText) {
      std::cerr << style4 << "\nError: " << exceptionText.what() << end
                << "\n\n";
    }
  }
  while (true) {
    std::cout << style3 << " please enter size of 2-st matrix            "
              << end1 << std::endl;
    try {
      sizeSecond = win.getSizesFromCin();
      std::cout << std::endl;
      break;
    } catch (std::exception &exceptionText) {
      std::cerr << style4 << "\nError: " << exceptionText.what() << end
                << "\n\n";
    }
  }
}

void ConsoleInterface::handleIncorrectSizes() {
  if (sizeFirst.second != sizeSecond.first) {
    std::cout << style4 << "\nError: "
              << "Matrix should have AxB and CxD sizes, where B==C" << end
              << "\n\n";
    createMatrix();
  }
}

void ConsoleInterface::setDataManual(int choiceMtrx) {
  std::cout << style3 << " please enter elements of " << choiceMtrx;
  if (choiceMtrx == 1)
    std::cout << "-st matrix        " << end1 << std::endl;
  else if (choiceMtrx == 2)
    std::cout << "-nd matrix        " << end1 << std::endl;
  try {
    if (choiceMtrx == 1)
      win.matrixManualSet(sizeFirst.first, sizeFirst.second, choiceMtrx);
    else if (choiceMtrx == 2)
      win.matrixManualSet(sizeSecond.first, sizeSecond.second, choiceMtrx);
    std::cout << std::endl;
  } catch (std::exception &exceptionText) {
    std::cerr << style4 << "\nError: " << exceptionText.what() << end << "\n\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    setDataManual(choiceMtrx);
  }
}

void ConsoleInterface::inputMenu() {
  menuText();
  int choice;
  if (std::cin >> choice) {
    if (choice == 1) {
      setDataManual(1);
      setDataManual(2);
      printAndRunMenu();
    } else if (choice == 2) {
      win.matrixRandomSet(sizeFirst.first, sizeFirst.second, 1);
      win.matrixRandomSet(sizeSecond.first, sizeSecond.second, 2);
      printAndRunMenu();
    } else if (choice == 3) {
      createMatrix();
      handleIncorrectSizes();
      inputMenu();
    } else if (choice == 0) {
      return;
    } else {
      handleIncorrectMenuChoice();
      inputMenu();
    }
  } else {
    handleIncorrectMenuChoice();
    inputMenu();
  }
}

void ConsoleInterface::handleIncorrectMenuChoice() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << style4 << "\nError: incorrect input, try again " << end
            << std::endl;
}

void ConsoleInterface::printAndRunMenu() {
  printMenu();
  int choice;
  if (std::cin >> choice) {
    if (choice == 1) {
      runAlgorithm();
    } else if (choice == 2) {
      std::cout << "\n";
      printMatrix(win.getFirstMatrix(), "1-st matrix");
      printMatrix(win.getSecondMatrix(), "2-nd matrix");
      printAndRunMenu();
    } else {
      handleIncorrectMenuChoice();
      printAndRunMenu();
    }
  } else {
    handleIncorrectMenuChoice();
    printAndRunMenu();
  }
}

void ConsoleInterface::runAlgorithm() {
  Simpletimer timer;
  double runtime;
  std::cout << style4 << "\nEnter number of executions (1 - 10000)" << end
            << std::endl;
  int N;
  std::cin >> N;
  // Run algorithm without multithreads
  timer.startTime();
  for (int i = 0; i < N; i++) {
    win.runWinogradAlgo();
  }
  runtime = timer.getTime();
  std::cout << std::endl;
  std::cout << style3 << " 1. Run Algorithm in Simple way              " << end
            << std::endl;
  std::cout << style4 << "\nRuntime = " << runtime << " s" << end1 << std::endl;
  // Run algorithm with multithreads (pipeline parallelism)
  timer.startTime();
  for (int i = 0; i < N; i++) {
    win.runWinogradAlgoMultithread();
  }
  runtime = timer.getTime();
  std::cout << std::endl;
  std::cout << style3 << " 2. Run Algorithm in Pipeline Parallelism    " << end
            << std::endl;
  std::cout << style4 << "\nRuntime = " << runtime << " s" << end1 << std::endl;
  // Run algorithm with classical parallelism
  runClassicalParallelism(N);
  exitOrRestart();
}

void ConsoleInterface::runClassicalParallelism(int n) {
  Simpletimer timer;
  int t = 3;
  int posibleThreads = std::thread::hardware_concurrency();
  // std::cout << posibleThreads << std::endl;
  int maxThreads = std::min(n, posibleThreads);
  std::vector<std::thread> threads;
  for (int i = std::min(maxThreads, 2); i <= maxThreads; i += i > 2 ? 4 : 2) {
    threads.clear();
    int executionsForThread = std::max(1, n / i);
    timer.startTime();
    for (int j = 0; j < i; j++) {
      threads.push_back(std::thread([&]() {
        for (int k = 0; k < executionsForThread; k++) {
          win.runWinogradAlgo();
        }
      }));
    }
    for (auto &thread : threads) thread.join();
    double runtime = timer.getTime();
    std::cout << std::endl;
    std::cout << style3 << t << ". Classical Parallelism:  " << i
              << " threads         " << end << std::endl;
    std::cout << style4 << "\nRuntime = " << runtime << " s" << end1
              << std::endl;
    t++;
  }
}

void ConsoleInterface::exitOrRestart() {
  endMenu();
  int choice;
  if (std::cin >> choice) {
    if (choice == 1) {
      printMatrix(win.getResultMatrix(), "Result matrix");
      exitOrRestart();
    } else if (choice == 2) {
      std::cout << "\n";
      startProgram();
    } else if (choice == 0) {
      return;
    } else {
      handleIncorrectMenuChoice();
      endMenu();
    }
  } else {
    handleIncorrectMenuChoice();
    endMenu();
  }
}

void ConsoleInterface::printMatrix(s21::Matrix mtrx,
                                   const std::string &choiceMtrx) {
  std::cout << style4 << choiceMtrx << ":\n";
  for (int i = 0; i < mtrx.getRows(); i++) {
    for (int j = 0; j < mtrx.getCols(); j++) {
      printf("%5.0f ", mtrx(i, j));
    }
    std::cout << std::endl;
  }
  std::cout << "\n" << end;
}

void ConsoleInterface::informationPart() {
  std::cout << style1 << "\n---------------------------------------------"
            << end << std::endl;
  std::cout << style2 << "             WELCOME TO PARALLELS            " << end
            << std::endl;
  std::cout << style1 << "---------------------------------------------" << end
            << std::endl;
  std::cout << style4 << "             program created  by" << end << std::endl;
  std::cout << style4 << "             dpoliwhi & esharika" << end << std::endl;
  std::cout << style1 << "---------------------------------------------" << end1
            << std::endl;
}

void ConsoleInterface::printMenu() {
  std::cout << style1 << "---------------------------------------------" << end
            << std::endl;
  std::cout << style2 << "               CHOISE ACTION                 " << end
            << std::endl;
  std::cout << style1 << "---------------------------------------------" << end1
            << std::endl;
  std::cout << style3 << " 1. Run Winograd Algorithm                   " << end
            << std::endl;
  std::cout << style3 << " 2. Print matrixes                           " << end1
            << std::endl;
}

void ConsoleInterface::menuText() {
  std::cout << style1 << "---------------------------------------------" << end
            << std::endl;
  std::cout << style2 << "                    MENU                     " << end
            << std::endl;
  std::cout << style1 << "---------------------------------------------" << end1
            << std::endl;
  std::cout << style3 << " 1. Manual input data                        " << end
            << std::endl;
  std::cout << style3 << " 2. Random create data                       " << end
            << std::endl;
  std::cout << style3 << " 3. Reinput sizes of matrix                  " << end
            << std::endl;
  std::cout << style3 << " 0. Exit from the program                    " << end1
            << std::endl;
}

void ConsoleInterface::endMenu() {
  std::cout << style1 << "---------------------------------------------" << end
            << std::endl;
  std::cout << style2 << "              ALGORITHM COMPLITED            " << end
            << std::endl;
  std::cout << style1 << "---------------------------------------------" << end1
            << std::endl;
  std::cout << style3 << " 1. Print result matrix                      " << end
            << std::endl;
  std::cout << style3 << " 2. Restart program                          " << end
            << std::endl;
  std::cout << style3 << " 0. Exit from the program                    " << end1
            << std::endl;
}

}  // namespace s21

// "-pthread",
// "${file}",
// "Matrix/*.cpp",
// "sle/main.cpp",
// "sle/*/*.cpp",
