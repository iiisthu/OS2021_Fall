#ifndef DEADLOCK_LIB_RESOURCE_MANAGER_H_
#define DEADLOCK_LIB_RESOURCE_MANAGER_H_

#include <map>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "thread_manager.h"

namespace proj2 {

enum RESOURCE {
    GPU = 0,
    MEMORY,
    DISK,
    NETWORK
};

class ResourceManager {
public:
    ResourceManager(ThreadManager *t, std::map<RESOURCE, int> init_count): \
        resource_amount(init_count), tmgr(t) {}
    std::map<std::thread::id, int> GPU_request;
    std::map<std::thread::id, int> MEMORY_request;
    std::map<std::thread::id, int> DISK_request;
    std::map<std::thread::id, int> NETWORK_request;
    std::map<std::thread::id, int> GPU_alloc;
    std::map<std::thread::id, int> MEMORY_alloc;
    std::map<std::thread::id, int> DISK_alloc;
    std::map<std::thread::id, int> NETWORK_alloc;
    std::map<std::thread::id, bool> is_suspend;
    //void request_claim_release(RESOURCE , std::thread::id); 
    bool safe(int GPU_amount, int MEMORY_amount, int DISK_amount, int NETWORK_amount, std::map<std::thread::id, int> GPU_request, std::map<std::thread::id, int> MEMORY_request, std::map<std::thread::id, int> DISK_request, std::map<std::thread::id, int> NETWORK_request, std::map<std::thread::id, int> GPU_alloc, std::map<std::thread::id, int> MEMORY_alloc, std::map<std::thread::id, int> DISK_alloc, std::map<std::thread::id, int> NETWORK_alloc);
    void budget_claim(std::map<RESOURCE, int> budget);
    int request(RESOURCE, int amount);
    void release(RESOURCE, int amount);
private:
    std::map<RESOURCE, int> resource_amount;
    std::map<RESOURCE, std::mutex> resource_mutex;
    std::condition_variable request_cv;
    std::mutex request_mutex;
    std::mutex is_suspend_mutex;
    std::map<RESOURCE, std::condition_variable> resource_cv;
    ThreadManager *tmgr;
};

}  // namespce: proj2

#endif