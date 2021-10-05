#ifndef THREAD_LIB_UTILS_H_
#define THREAD_LIB_UTILS_H_

#include <string>
#include <vector>
#include <iostream>
#include <chrono>  // for AutoTimer function

// For colored outputs in terminal
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

namespace proj1 {

// TODO(xuw): better to define this as a enum type
static const int kOrderInit = 0;
static const int kOrderUpdate = 1;

template <class T>
inline void embbedingAssert(bool condition, char const *msg, T error) {
    if (!condition) {
        std::cerr << msg << std::endl;
        throw error;
    }
}

void a_slow_function(int seconds);

double sigmoid(double x);

double sigmoid_backward(double x);

double binary_cross_entropy(double y_true, double y_pred);

double binary_cross_entropy_backward(double y_true, double y_pred);

class AutoTimer {
 public:
  AutoTimer(std::string name);
  ~AutoTimer(); 
 private:
  std::string m_name;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_beg;
};

} // namespace proj1
#endif // THREAD_LIB_UTILS_H_
