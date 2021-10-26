#include <mutex>
#include <condition_variable>
#include "resource_manager.h"

namespace proj2 {

void ResourceManager::request(RESOURCE r, int amount) {
    if (amount <= 0)  return;

    std::unique_lock<std::mutex> lk(this->resource_mutex[r]);
    this->resource_cv[r].wait(
        lk, [this, r, amount] { return this->resource_amount[r] >= amount; }
    );
    this->resource_amount[r] -= amount;
    this->resource_mutex[r].unlock();
}

void ResourceManager::release(RESOURCE r, int amount) {
    if (amount <= 0)  return;
    std::unique_lock<std::mutex> lk(this->resource_mutex[r]);
    this->resource_amount[r] += amount;
    this->resource_cv[r].notify_all();
}

} // namespace: proj2
