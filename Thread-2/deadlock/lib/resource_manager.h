#ifndef DEADLOCK_LIB_RESOURCE_MANAGER_H_
#define DEADLOCK_LIB_RESOURCE_MANAGER_H_

#include <map>
#include <mutex>

namespace proj2 {

enum RESOURCE {
    GPU = 0,
    MEMORY,
    DISK
};

class ResourceManager {
public:
    ResourceManager(std::map<RESOURCE, int> init_count): \
        resource_amount(init_count) {}
    int request(RESOURCE, int amount);
    int release(RESOURCE, int amount);
private:
    std::map<RESOURCE, int> resource_amount;
    std::map<RESOURCE, std::mutex> resource_mutex;
};

}  // namespce: proj2

#endif