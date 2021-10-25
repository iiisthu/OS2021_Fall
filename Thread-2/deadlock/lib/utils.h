#ifndef DEADLOCK_LIB_UTILS_H_
#define DEADLOCK_LIB_UTILS_H_

#include <string>
#include <tuple>
#include <vector>
#include <chrono>

namespace proj2 {

void a_slow_function(int seconds);

int randint(int lower, int upper);  // sample int from [lower, upper]

bool randbit();

class AutoTimer {
 public:
  AutoTimer(std::string name);
  ~AutoTimer(); 
 private:
  std::string m_name;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_beg;
};

}  // namespace: proj2

#endif