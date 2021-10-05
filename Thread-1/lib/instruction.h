#ifndef THREAD_LIB_INSTRUCTION_H_
#define THREAD_LIB_INSTRUCTION_H_

#include <string>
#include <vector>

namespace proj1 {

enum InstructionOrder {
    INIT_EMB = 0,
    UPDATE_EMB,
    RECOMMEND
};

struct Instruction {
    Instruction(std::string);
    InstructionOrder order;
    std::vector<int> payloads;
};

using Instructions = std::vector<Instruction>;

Instructions read_instructrions(std::string);

} // namespace proj1
#endif  // THREAD_LIB_INSTRUCTION_H_