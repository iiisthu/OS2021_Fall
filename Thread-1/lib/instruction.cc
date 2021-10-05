#include <string>
#include <sstream>
#include <fstream>
#include "instruction.h"

namespace proj1 {

Instruction::Instruction(std::string line) {
    std::stringstream ss(line);
    int data;
    ss >> data;
    this->order = (InstructionOrder) data;
    while (ss >> data) {
        this->payloads.push_back(data);
    }
}

Instructions read_instructrions(std::string filename) {
    std::ifstream ifs(filename);
    std::string line;
    Instructions data;
    if (ifs.is_open()) {
        while(std::getline(ifs, line)) {
            data.push_back(Instruction(line));
        }
        ifs.close();
    }
    return data;
}

} // namespace proj1