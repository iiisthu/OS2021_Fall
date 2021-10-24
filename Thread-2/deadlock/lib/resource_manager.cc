#include "resource_manager.h"

namespace proj2 {

int ResourceManager::request(RESOURCE r, int amount) {
    if (amount < 0)  return -1;  // Negative amount
    if (amount == 0) return 0;
    this->resource_mutex[r].lock();
    if (this->resource_amount[r] >= amount) {
        this->resource_amount[r] -= amount;
        this->resource_mutex[r].unlock();
        return 0;
    }
    this->resource_mutex[r].unlock();
    return 1;  // Not enough resource
}

int ResourceManager::release(RESOURCE r, int amount) {
    if (amount < 0)  return -1;
    if (amount == 0) return 0;
    this->resource_mutex[r].lock();
    this->resource_amount[r] += amount;
    this->resource_mutex[r].unlock();
    return 0;
}

} // namespace: proj2
