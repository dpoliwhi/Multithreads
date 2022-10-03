#pragma once

#include <limits.h>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "../../SimpleTimer.h"
#include "aco.h"
#include "s21_graph.h"

namespace s21 {

class GraphAlgorithms {
 private:
  std::vector<int> correctOutput(std::vector<int> vec);
  void checkGraph(const Graph &graph);

 public:
  std::pair<TsmResult, double> solveTravelingSalesmanProblem(const Graph &graph,
                                                             int N);
  std::pair<TsmResult, double> solveTravelingSalesmanProblemMultithreads(
      const Graph &graph, int N);
};

}  // namespace s21
