#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "lib/utils.h"
#include "lib/workload.h"
#include "lib/resource_manager.h"

namespace proj2 {

std::map<RESOURCE, int> read_resource_budget(std::ifstream &ifs) {
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

std::vector<Instruction> read_instruction(std::ifstream &ifs) {
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

void run_instruction(ResourceManager *mgr, Instruction inst) {
    auto rsc1 = static_cast<RESOURCE>(inst[0]);
    auto rsc2 = static_cast<RESOURCE>(inst[1]);
    int st1 = inst.size() > 4? inst[4]: -1;
    int st2 = inst.size() > 5? inst[5]: -1;
    int ro = inst.size() > 6? inst[6]: -1;
    workload(mgr, rsc1, rsc2, inst[2], inst[3], st1, st2, ro);
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

    // Run the instructions in parallel without deadlocks
    return 0;
}
