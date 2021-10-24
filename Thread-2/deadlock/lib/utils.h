#ifndef DEADLOCK_LIB_UTILS_H_
#define DEADLOCK_LIB_UTILS_H_

#include <string>
#include <vector>

namespace proj2 {

void a_slow_function(int seconds);

int randint(int lower, int upper);  // sample int from [lower, upper]

bool randbit();

using Instruction = std::vector<int>;

std::vector<Instruction> read_instruction(std::string file);

}  // namespace: proj2

#endif