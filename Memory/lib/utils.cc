#include <chrono>
#include <thread>
#include <cstdlib>
#include <iostream>
#include "utils.h"

namespace proj3 {

void a_slow_function(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

AutoTimer::AutoTimer(std::string name): 
        m_name(std::move(name)),
        m_beg(std::chrono::high_resolution_clock::now()) { 
    }

AutoTimer::~AutoTimer() {
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - m_beg);
    std::cout << m_name << " : " << dur.count() << " usec\n";
}

} // namespce: proj3
