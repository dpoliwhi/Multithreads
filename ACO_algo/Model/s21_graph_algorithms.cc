#include "s21_graph_algorithms.h"

namespace s21 {

std::vector<int> GraphAlgorithms::correctOutput(std::vector<int> vec) {
  std::vector<int> result;
  for (size_t i = 0; i < vec.size(); i++) {
    result.push_back(vec[i] + 1);
  }
  return result;
}

void GraphAlgorithms::checkGraph(const Graph &graph) {
  if (graph.getDirectionType() == directed ||
      graph.getWeightType() == unweighted || graph.getSize() <= 2) {
    throw std::invalid_argument("Wrong graph");
  }
}

std::pair<TsmResult, double> GraphAlgorithms::solveTravelingSalesmanProblem(
    const Graph &graph, int N) {
  Simpletimer timer;
  timer.startTime();
  checkGraph(graph);
  ACO algo;
  std::pair<TsmResult, double> result;
  for (int i = 0; i < N; i++) {
    result.first = algo.TSPSolve(graph);
  }
  result.first.vertices = correctOutput(result.first.vertices);
  result.second = timer.getTime();
  return result;
}

std::pair<TsmResult, double>
GraphAlgorithms::solveTravelingSalesmanProblemMultithreads(const Graph &graph,
                                                           int N) {
  Simpletimer timer;
  timer.startTime();
  checkGraph(graph);
  ACO algo;
  std::pair<TsmResult, double> result;
  for (int i = 0; i < N; i++) {
    result.first = algo.TSPSolveMultithreads(graph);
  }
  result.first.vertices = correctOutput(result.first.vertices);
  result.second = timer.getTime();
  return result;
}

}  // namespace s21
