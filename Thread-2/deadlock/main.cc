#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "lib/utils.h"
#include "lib/workload.h"
#include "lib/resource_manager.h"

namespace proj2 {

std::map<RESOURCE, int> read_resource_budget(std::ifstream ifs) {
    int amount;
    std::string line;
    std::map<RESOURCE, int> budget;
    if(std::getline(ifs, line)) {
        std::stringstream ss(line);
        for (RESOURCE r = GPU; r <= NETWORK; r = RESOURCE(r + 1)) {
            ss >> amount;
            budget[r] = amount;
        }
    }
    return budget;
}

using Instruction = std::vector<int>;

std::vector<Instruction> read_instruction(std::ifstream ifs) {
    int value;
    std::string line;
    std::vector<Instruction> result;
    while(std::getline(ifs, line)) {
        Instruction inst;
        std::stringstream ss(line);
        while(ss >> value) {
            inst.push_back(value);
        }
        result.push_back(inst);
    }
    return result;
}

}

int main(int argc, char *argv[]) {
    // Read the data file
    std::string datafile(argc > 1? argv[1]: "data/example.in");
    std::ifstream ifs(datafile);
    if (!ifs.is_open())
        return 1;
    proj2::ResourceManager *mgr = \
        new proj2::ResourceManager(proj2::read_resource_budget(ifs));
    std::vector<proj2::Instruction> instructions = proj2::read_instruction(ifs);
    ifs.close();

    // Run the instructions in parallel
    return 0;
}
