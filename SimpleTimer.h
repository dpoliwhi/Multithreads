#include <chrono>
#include <iostream>
#include <string>

class Simpletimer {
 private:
  std::chrono::high_resolution_clock::time_point start, end;
  std::chrono::duration<double> runtime;

 public:
  double getTime() {
    end = std::chrono::high_resolution_clock::now();
    runtime = end - start;
    return runtime.count();
  }
  Simpletimer() {
    start = std::chrono::high_resolution_clock::now();
  }
  ~Simpletimer() {}
};
