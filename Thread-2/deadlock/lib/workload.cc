#include "workload.h"
#include "resource_manager.h"

namespace proj2 {

int BaseWorkload::request(ResourceManager* mgr, RESOURCE r, int amount) {
    int code = mgr->request(r, amount);
    if(code == 0) {
        this->resource_amount[r] += amount;
    }
}

int BaseWorkload::release(ResourceManager* mgr, RESOURCE r, int amount) {
    int code = mgr->request(r, amount);
    if(code == 0) {
        this->resource_amount[r] -= amount;
    }
}

}