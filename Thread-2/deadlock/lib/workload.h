#ifndef DEADLOCK_LIB_WORKLOAD_H_
#define DEADLOCK_LIB_WORKLOAD_H_

#include "resource_manager.h"

namespace proj2 {

const int MIN_RUNNING_TIME = 3;
const int MAX_RUNNING_TIME = 10;

void workload(
    ResourceManager *mgr,
    RESOURCE rsc1,
    RESOURCE rsc2,
    int rsc1_amount,
    int rsc2_amount,
    int sleep_time1 = -1,  // -1 for random
    int sleep_time2 = -1,   // -1 for random
    int reverse_order = -1  // -1 for random, 1 for true, 0 for false
);

}  // namespce: proj2

#endif