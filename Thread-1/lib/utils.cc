#include <cmath>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include "utils.h"

namespace proj1 {

void a_slow_function(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_backward(double x) {
    double y = sigmoid(x);
    return y * (1.0 - y);
}

double binary_cross_entropy(double y_true, double y_pred) {
    double eps = 1e-8;
    return y_true * log(eps + y_pred) \
        + (1.0 - y_true) * log(1.0 - y_pred + eps);
}

double binary_cross_entropy_backward(double y_true, double y_pred) {
    double eps = 1e-8;
    return (y_true - y_pred) / (eps + (1.0 - y_pred) * y_pred);
}

AutoTimer::AutoTimer(std::string name) : 
        m_name(std::move(name)),
        m_beg(std::chrono::high_resolution_clock::now()) { 
    }

AutoTimer::~AutoTimer() {
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - m_beg);
    std::cout << m_name << " : " << dur.count() << " usec\n";
}

} // namespace proj1