#ifndef DEADLOCK_LIB_WORKLOAD_H_
#define DEADLOCK_LIB_WORKLOAD_H_

#include <chrono>
#include <thread>

namespace proj2 {

void a_slow_function(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
}

#endif