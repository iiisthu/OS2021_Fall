#ifndef DEADLOCK_LIB_WORKLOAD_H_
#define DEADLOCK_LIB_WORKLOAD_H_

#include <map>
#include "resource_manager.h"

namespace proj2 {

class BaseWorkload {
public:
    int request(ResourceManager*, RESOURCE, int);
    int release(ResourceManager*, RESOURCE, int);
protected:
    std::map<RESOURCE, int> resource_amount;
};

class Workload1: public BaseWorkload {
public:
    void do_work(std::map<RESOURCE, int> max_demand);
};

class Workload2: public BaseWorkload {
public:
    void do_work(std::map<RESOURCE, int> max_demand);
};

class Workload3: public BaseWorkload {
public:
    void do_work(std::map<RESOURCE, int> max_demand);
};

}  // namespce: proj2

#endif