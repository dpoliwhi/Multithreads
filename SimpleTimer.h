#include <chrono>
#include <iostream>
#include <string>

class Simpletimer {
 private:
  std::chrono::high_resolution_clock::time_point start, end;
  std::chrono::duration<double> runtime;

 public:
  void startTime() { start = std::chrono::high_resolution_clock::now(); }
  double getTime() {
    end = std::chrono::high_resolution_clock::now();
    runtime = end - start;
    return runtime.count();
  }
  Simpletimer() {}
  ~Simpletimer() {}
};
