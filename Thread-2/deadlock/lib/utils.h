#ifndef DEADLOCK_LIB_UTILS_H_
#define DEADLOCK_LIB_UTILS_H_

#include <string>
#include <tuple>
#include <vector>

namespace proj2 {

void a_slow_function(int seconds);

int randint(int lower, int upper);  // sample int from [lower, upper]

bool randbit();

}  // namespace: proj2

#endif