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

}
