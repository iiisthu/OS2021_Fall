#include <map>
#include <thread>
#include <utility>
#include "workload.h"
#include "resource_manager.h"
#include "utils.h"

namespace proj2 {

void workload(ResourceManager *mgr,
              RESOURCE rsc1, RESOURCE rsc2,
              int rsc1_amount, int rsc2_amount,
              int sleep_time1, int sleep_time2,
              int reverse_order) {
    // Inform the resource manager about resource budget
    std::map<RESOURCE, int> budget = {
        {rsc1, rsc1_amount}, {rsc2, rsc2_amount}
    };
    mgr->budget_claim(budget);
    // Randomness
    if (reverse_order < 0) {
        reverse_order = randbit();
    }
    if (reverse_order > 0) {
        std::swap(rsc1, rsc2);
        std::swap(rsc1_amount, rsc2_amount);
    }
    sleep_time1 = sleep_time1 < 0? randint(MIN_RUNNING_TIME, MAX_RUNNING_TIME): sleep_time1;
    sleep_time2 = sleep_time2 < 0? randint(MIN_RUNNING_TIME, MAX_RUNNING_TIME): sleep_time2;

    // Request resource -> running -> request another -> running -> release
    if (mgr->request(rsc1, rsc1_amount) < 0)  // I'm killed
        return;
    a_slow_function(sleep_time1);
    if (mgr->request(rsc2, rsc2_amount) < 0) // I'm killed
        return;
    a_slow_function(sleep_time2);
    mgr->release(rsc1, rsc1_amount);
    mgr->release(rsc2, rsc2_amount);
}

} // namespace: proj2
