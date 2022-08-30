#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Work {
 public:
  mutex mtx;
  int doWork(int a, int b) {
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "======== do work start ========" << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
    cout << "======== do work finish ========" << endl;
    return a + b;
  }
  void doWork_print(int a, int b) {
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "======== do work start ========" << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
    cout << "sum = " << a + b << endl;
    cout << "======== do work finish ========" << endl;
  }
  void doWork_ref(int a, int b, int& sum) {
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "======== do work start ========" << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
    sum = a + b;
    cout << "======== do work finish ========" << endl;
  }
  void doWithMutex(char x) {
    this_thread::sleep_for(chrono::milliseconds(2000));
    {
      lock_guard<mutex> guard(mtx);
      for (int i = 0; i < 10; i++) {
        this_thread::sleep_for(chrono::milliseconds(20));
        for (int j = 0; j < 10; j++) {
          this_thread::sleep_for(chrono::milliseconds(20));
          cout << x;
        }
        cout << endl;
      }
    }
    this_thread::sleep_for(chrono::milliseconds(2000));
  }
};

int main() {
  Work one;
  thread t1([&]() { one.doWithMutex('*'); });
  thread t2([&]() { one.doWithMutex('$'); });
  // one.doWithMutex('*');
  // one.doWithMutex('$');
  // for (int i = 0; i < 10; i++) {
  //   cout << "id потока = " << this_thread::get_id() << " метод main \t" << i << endl;
  //   this_thread::sleep_for(chrono::milliseconds(500));
  // }
  t1.join();
  t2.join();

  return 0;
}
