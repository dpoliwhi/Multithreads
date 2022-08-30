#include "s21_console_interface.h"

#include <iostream>

namespace s21 {

void ConsoleInterface::startProgram() {
  informationPart();
  fileReading();
}

void ConsoleInterface::informationPart() {
  std::cout << style1 << "\n---------------------------------------------" << end << std::endl;
  std::cout << style2 << "         WELCOME TO SIMPLE NAVIGATOR         " << end << std::endl;
  std::cout << style1 << "---------------------------------------------" << end << std::endl;
  std::cout << style4 << "             program created  by" << end << std::endl;
  std::cout << style4 << "             dpoliwhi & esharika" << end << std::endl;
  std::cout << style1 << "---------------------------------------------" << end1 << std::endl;
}

void ConsoleInterface::fileReading() {
  while (true) {
    std::cout << style3 << " please enter file name                      " << end << std::endl;
    std::cout << std::endl;
    std::string filename;
    std::cin >> filename;
    try {
      mainGraph.clearDataFile();
      mainGraph.loadGraphFromFile("../datasets/" + filename);
      break;
    } catch (std::exception &exceptionText) {
      std::cerr << style4 << "\nError: " << exceptionText.what() << end << "\n\n";
    }
  }
  algorithmMenu();
}

void ConsoleInterface::saveToDot() {
  std::cout << "\n" << style3 << " please enter file name to save              " << end1 << std::endl;
  std::string filename;
  std::cin >> filename;
  mainGraph.exportGraphToDot(filename);
  std::cout << "\n" << style3 << " file successfully saved in Graphs directory " << end1 << std::endl;
  std::cerr << style4 << "to create a png file\ninstall and use the graphViz utility\n" << end1;
  menuOrExit();
}

void ConsoleInterface::algorithmMenu() {
  menuText();
  int choice;
  std::cin >> choice;
  if (choice == 1) {
    AntColonyOptimization();
  } else if (choice == 2) {
    saveToDot();
  } else if (choice == 3) {
    fileReading();
  } else if (choice == 0) {
    return;
  } else {
    std::cout << style4 << "\nError: incorrect input, try again " << end << std::endl;
    algorithmMenu();
  }
}

void ConsoleInterface::AntColonyOptimization() {
  try {
    std::cout << style4 << "\nenter how many times to keep track of the time (1 - 1000)" << end1 << std::endl;
    int N;
    std::cin >> N;
    std::pair<TsmResult, double> res;
    res = algorithms.solveTravelingSalesmanProblem(mainGraph, N);
    std::cout << std::fixed;
    std::cout << style4 << "1) Ant Colony Optimization Algoritm\n";
    // std::cout << std::setprecision(5);
    printVector(res.first.vertices);
    // std::cout << std::setprecision(0);
    std::cout << style4 << "DISTANCE: " << res.first.distance << end1 << std::endl;
    std::cout << style4 << "RUNTIME: " << res.second << "sec" << std::endl;

    res = algorithms.solveTravelingSalesmanProblemMultithreads(mainGraph, N);
    std::cout << std::fixed;
    std::cout << style4 << "2) Ant Colony Optimization Algoritm with multithreads\n";
    // std::cout << std::setprecision(5);
    printVector(res.first.vertices);
    // std::cout << std::setprecision(0);
    std::cout << style4 << "DISTANCE: " << res.first.distance << end1 << std::endl;
    std::cout << style4 << "RUNTIME: " << res.second << "sec" << std::endl;
    menuOrExit();
  } catch (std::exception &exceptionText) {
    std::cerr << style4 << "\nError: " << exceptionText.what() << end1 << "\n";
    menuOrExit();
  }
}

void ConsoleInterface::printVector(std::vector<int> path) {
  std::cout << style4 << "\nPATH: ";
  for (size_t i = 0; i < path.size(); i++) {
    std::cout << path[i] << " ";
  }
  std::cout << "\n" << end1;
}

void ConsoleInterface::printMatrix(s21::Matrix res) {
  std::cout << style4 << "\nMATRIX:\n";
  for (int i = 0; i < res.getRows(); i++) {
    for (int j = 0; j < res.getCols(); j++) {
      std::cout << res(i, j);
      if (res(i, j) < 10)
        std::cout << "   ";
      else if (res(i, j) >= 10 && res(i, j) < 100)
        std::cout << "  ";
      else
        std::cout << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "\n" << end;
}

void ConsoleInterface::menuOrExit() {
  std::cout << style3 << " to return to the menu press 1               " << end << std::endl;
  std::cout << style3 << " to exit the program press 0                 " << end1 << std::endl;
  int choice;
  std::cin >> choice;
  if (choice == 1) {
    algorithmMenu();
  } else if (choice == 0) {
    return;
  } else {
    std::cout << style4 << "\nError: incorrect input, try again " << end << std::endl;
    menuOrExit();
  }
}

void ConsoleInterface::menuText() {
  std::cout << style1 << "---------------------------------------------" << end << std::endl;
  std::cout << style2 << "               ALGORITHMS MENU               " << end << std::endl;
  std::cout << style1 << "---------------------------------------------" << end1 << std::endl;
  std::cout << style3 << " 1. Ant colony algorithm                     " << end << std::endl;
  std::cout << style3 << " 2. Save graph to .dot                       " << end << std::endl;
  std::cout << style3 << " 3. Upload new file                          " << end << std::endl;
  std::cout << style3 << " 0. Exit from the program                    " << end1 << std::endl;
}

}  // namespace s21
