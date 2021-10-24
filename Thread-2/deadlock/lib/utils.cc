#include <chrono>
#include <thread>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "utils.h"

namespace proj2 {

void a_slow_function(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

int randint(int lower, int upper) {
    return rand() % (upper - lower + 1) + lower;
}

bool randbit() {
    return rand() % 2 > 0;
}

std::vector<Instruction> read_instruction(std::string file) {
    std::vector<Instruction> result;
    std::ifstream ifs(file);
    std::string line;
    int data;
    if (ifs.is_open()) {
        while (std::getline(ifs, line)) {
            Instruction inst;
            std::stringstream ss(line);
            while (ss >> data) {
                inst.push_back(data);
            }
            result.push_back(inst);
        }
    }
    return result;
}

}
