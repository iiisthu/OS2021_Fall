#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include "resource_manager.h"
#include "thread_manager.h"

namespace proj2 {
/*int ResourceManager::request(RESOURCE r, int amount) {
    if (amount <= 0)  return 1;
    std::unique_lock<std::mutex> lk(this->resource_mutex[r]);
    std::unique_lock<std::mutex> lck(is_suspend_mutex);
    is_suspend[std::this_thread::get_id()] = false;
    is_suspend_mutex.unlock();*/
    /* while (true) {
        if (this->resource_cv[r].wait_for(
            lk, std::chrono::milliseconds(100),
            [this, r, amount] { return this->resource_amount[r] >= amount; }
        )) {
            break;
        } else {
            auto this_id = std::this_thread::get_id();
            /* HINT: If you choose to detect the deadlock and recover,
                     implement your code here to kill and restart threads.
                     Note that you should release this thread's resources
                     properly.
             */
    /*       if (tmgr->is_killed(this_id)) {
                return -1;
            }
        }
    }*/
    /*while(true) {
        //std::unique_lock<std::mutex> lock(request_mutex);
        std::unique_lock<std::mutex> lck(is_suspend_mutex);
        if (amount > this->resource_amount[r]) {
            //std::unique_lock<std::mutex> lck(is_suspend_mutex);
            is_suspend[std::this_thread::get_id()] = true;
            is_suspend_mutex.unlock();
            std::cout<<"+++"<<std::this_thread::get_id()<<is_suspend[std::this_thread::get_id()]<<std::endl;
            //request_mutex.unlock();
            this->resource_cv[r].wait(lk);
            std::unique_lock<std::mutex> lck(is_suspend_mutex);
            is_suspend[std::this_thread::get_id()] = false;
            is_suspend_mutex.unlock();
            std::cout<<"wakeup"<<std::this_thread::get_id()<<is_suspend[std::this_thread::get_id()]<<std::endl;
        }
        else {
            this->resource_amount[r] -= amount;
            std::thread::id this_id = std::this_thread::get_id();
            if (r==0) GPU_request[this_id] -= amount;
            if (r==1) MEMORY_request[this_id] -= amount;
            if (r==2) DISK_request[this_id] -= amount;
            if (r==3) NETWORK_request[this_id] -= amount;
            if (r==0) GPU_alloc[this_id] += amount;
            if (r==1) MEMORY_alloc[this_id] += amount;
            if (r==2) DISK_alloc[this_id] += amount;
            if (r==3) NETWORK_alloc[this_id] += amount;
            int GPU_amount = this->resource_amount[GPU];
            int MEMORY_amount = this->resource_amount[MEMORY];
            int DISK_amount = this->resource_amount[DISK];
            int NETWORK_amount = this->resource_amount[NETWORK];
            //simulate by Banker's algorithm
            //std::lock_guard<std::mutex> lock(request_mutex);
            bool s = safe(GPU_amount, MEMORY_amount, DISK_amount, NETWORK_amount, GPU_request, MEMORY_request, DISK_request, NETWORK_request, GPU_alloc, MEMORY_alloc, DISK_alloc, NETWORK_alloc);
            if (s==true) {
                //request_mutex.unlock();
                is_suspend_mutex.unlock();
                std::cout<<"--"<<is_suspend[std::this_thread::get_id()]<<std::this_thread::get_id()<<std::endl;
                return 0;
            }
            else {
                this->resource_amount[r] += amount;
                if (r==0) GPU_alloc[std::this_thread::get_id()] -= amount;
                if (r==1) MEMORY_alloc[std::this_thread::get_id()] -= amount;
                if (r==2) DISK_alloc[std::this_thread::get_id()] -= amount;
                if (r==3) NETWORK_alloc[std::this_thread::get_id()] -= amount;
                is_suspend[std::this_thread::get_id()] = true;
                //request_mutex.unlock();
                is_suspend_mutex.unlock();
                std::cout<<"++"<<std::this_thread::get_id()<<is_suspend[std::this_thread::get_id()]<<std::endl;
                this->resource_cv[r].wait(lk);
                std::unique_lock<std::mutex> lck(is_suspend_mutex);
                is_suspend[std::this_thread::get_id()] = false;
                is_suspend_mutex.unlock();
                std::cout<<"wakeup"<<std::this_thread::get_id()<<is_suspend[std::this_thread::get_id()]<<std::endl;
                break;
            }
        }
    }
}*/

int ResourceManager::request(RESOURCE r, int amount) {
    if (amount <= 0)  return 1;
    //std::unique_lock<std::mutex> lock(this->resource_mutex);
    while(true) {
        std::unique_lock<std::mutex> lock(this->resource_mutex);
        if (amount > this->resource_amount[r]) {
            std::cout<<"+++"<<std::this_thread::get_id()<<std::endl;
            this->resource_cv.wait(lock);
            std::cout<<"wakeup"<<std::this_thread::get_id()<<is_suspend[std::this_thread::get_id()]<<std::endl;
            //std::unique_lock<std::mutex> lock(this->resource_mutex);
        }
        else {
            this->resource_amount[r] -= amount;
            std::thread::id this_id = std::this_thread::get_id();
            if (r==0) GPU_alloc[this_id] += amount;
            if (r==1) MEMORY_alloc[this_id] += amount;
            if (r==2) DISK_alloc[this_id] += amount;
            if (r==3) NETWORK_alloc[this_id] += amount;
            int GPU_amount = this->resource_amount[GPU];
            int MEMORY_amount = this->resource_amount[MEMORY];
            int DISK_amount = this->resource_amount[DISK];
            int NETWORK_amount = this->resource_amount[NETWORK];
            //simulate by Banker's algorithm
            bool s = safe(GPU_amount, MEMORY_amount, DISK_amount, NETWORK_amount, GPU_claim, MEMORY_claim, DISK_claim, NETWORK_claim, GPU_alloc, MEMORY_alloc, DISK_alloc, NETWORK_alloc);
            if (s==true) {
                std::cout<<"--"<<std::this_thread::get_id()<<std::endl;
                //this->resource_mutex.unlock();
                return 0;
            }
            else {
                this->resource_amount[r] += amount;
                if (r==0) GPU_alloc[std::this_thread::get_id()] -= amount;
                if (r==1) MEMORY_alloc[std::this_thread::get_id()] -= amount;
                if (r==2) DISK_alloc[std::this_thread::get_id()] -= amount;
                if (r==3) NETWORK_alloc[std::this_thread::get_id()] -= amount;
                std::cout<<"++"<<std::this_thread::get_id()<<std::endl;
                this->resource_cv.wait(lock);
                std::cout<<"wakeup"<<std::this_thread::get_id()<<std::endl;
            }
        }
    }
}

bool ResourceManager::safe(int GPU_amount, int MEMORY_amount, int DISK_amount, int NETWORK_amount, std::map<std::thread::id, int> GPU_claim, std::map<std::thread::id, int> MEMORY_claim, std::map<std::thread::id, int> DISK_claim, std::map<std::thread::id, int> NETWORK_claim, std::map<std::thread::id, int> GPU_alloc, std::map<std::thread::id, int> MEMORY_alloc, std::map<std::thread::id, int> DISK_alloc, std::map<std::thread::id, int> NETWORK_alloc) {
    std::map<std::thread::id, int> GPU_claim_c = GPU_claim;
    std::map<std::thread::id, int> MEMORY_claim_c = MEMORY_claim;
    std::map<std::thread::id, int> DISK_claim_c = DISK_claim;
    std::map<std::thread::id, int> NETWORK_claim_c = NETWORK_claim;
    std::map<std::thread::id, int> GPU_alloc_c = GPU_alloc;
    std::map<std::thread::id, int> MEMORY_alloc_c = MEMORY_alloc;
    std::map<std::thread::id, int> DISK_alloc_c = DISK_alloc;
    std::map<std::thread::id, int> NETWORK_alloc_c = NETWORK_alloc;
    bool possible = true;
    while (possible) {
        bool flag = false;
        std::map<std::thread::id, int>::iterator iter;
        for (iter = GPU_claim_c.begin(); iter != GPU_claim_c.end(); iter++) {
            std::thread::id this_id = iter->first;
            if (tmgr->is_killed(this_id)==true) {
                flag = true;
                std::cout<<"%%"<<std::this_thread::get_id()<<std::endl;
                GPU_claim_c.erase(iter);
                break;
            }
            if (GPU_claim_c[this_id]-GPU_alloc_c[this_id] <= GPU_amount && MEMORY_claim_c[this_id]-MEMORY_alloc_c[this_id] <= MEMORY_amount && DISK_claim_c[this_id]-DISK_alloc_c[this_id] <= DISK_amount && NETWORK_claim_c[this_id]-NETWORK_alloc_c[this_id] <= NETWORK_amount) {
                flag = true;
                GPU_amount += GPU_alloc_c[this_id];
                MEMORY_amount += MEMORY_alloc_c[this_id];
                DISK_amount += DISK_alloc_c[this_id];
                NETWORK_amount += NETWORK_alloc_c[this_id];
                std::cout<<"%%"<<std::this_thread::get_id()<<std::endl;
                GPU_claim_c.erase(iter);
                break;
            }
        }
        if (!flag) possible = false;
    }
    if (GPU_claim_c.size() == 0) return true;
    return false;
}

void ResourceManager::release(RESOURCE r, int amount) {
    if (amount <= 0)  return;
    std::unique_lock<std::mutex> lock(this->resource_mutex);
    this->resource_amount[r] += amount;
    std::thread::id this_id = std::this_thread::get_id();
    if (r==0) GPU_alloc[this_id] -= amount;
    if (r==1) MEMORY_alloc[this_id] -= amount;
    if (r==2) DISK_alloc[this_id] -= amount;
    if (r==3) NETWORK_alloc[this_id] -= amount;
    std::cout<<"!"<<std::this_thread::get_id()<<std::endl;
    this->resource_cv.notify_all();
    return;
}

/*void ResourceManager::budget_claim(std::map<RESOURCE, int> budget) {
    // This function is called when some workload starts.
    // The workload will eventually consume all resources it claims
    std::thread::id this_id = std::this_thread::get_id();
    GPU_request.insert(std::map<std::thread::id, int>::value_type(this_id, (budget.count(GPU)==1)?budget[GPU]:0));
    MEMORY_request.insert(std::map<std::thread::id, int>::value_type(this_id, (budget.count(MEMORY)==1)?budget[MEMORY]:0));
    DISK_request.insert(std::map<std::thread::id, int>::value_type(this_id, (budget.count(DISK)==1)?budget[DISK]:0));
    NETWORK_request.insert(std::map<std::thread::id, int>::value_type(this_id, (budget.count(NETWORK)==1)?budget[NETWORK]:0));
    GPU_alloc.insert(std::map<std::thread::id, int>::value_type(this_id, 0));
    MEMORY_alloc.insert(std::map<std::thread::id, int>::value_type(this_id, 0));
    DISK_alloc.insert(std::map<std::thread::id, int>::value_type(this_id, 0));
    NETWORK_alloc.insert(std::map<std::thread::id, int>::value_type(this_id, 0));
    std::cout<<"**"<<std::this_thread::get_id()<<budget[GPU]<<std::endl;
    std::unique_lock<std::mutex> lck(is_suspend_mutex);
    is_suspend.insert(std::map<std::thread::id, bool>::value_type(this_id, false));
    is_suspend_mutex.unlock();
    return;
}*/

void ResourceManager::budget_claim(std::map<RESOURCE, int> budget) {
    // This function is called when some workload starts.
    // The workload will eventually consume all resources it claims
    // set resource_claim, init resource_alloc, init is_suspend 
    std::unique_lock<std::mutex> lock(this->resource_mutex);
    std::thread::id this_id = std::this_thread::get_id();
    
    GPU_claim.insert(std::map<std::thread::id, int>::value_type(this_id, (budget.count(GPU)==1)?budget[GPU]:0));
    MEMORY_claim.insert(std::map<std::thread::id, int>::value_type(this_id, (budget.count(MEMORY)==1)?budget[MEMORY]:0));
    DISK_claim.insert(std::map<std::thread::id, int>::value_type(this_id, (budget.count(DISK)==1)?budget[DISK]:0));
    NETWORK_claim.insert(std::map<std::thread::id, int>::value_type(this_id, (budget.count(NETWORK)==1)?budget[NETWORK]:0));
   
    GPU_alloc.insert(std::map<std::thread::id, int>::value_type(this_id, 0));
    MEMORY_alloc.insert(std::map<std::thread::id, int>::value_type(this_id, 0));
    DISK_alloc.insert(std::map<std::thread::id, int>::value_type(this_id, 0));
    NETWORK_alloc.insert(std::map<std::thread::id, int>::value_type(this_id, 0));
    
    std::cout<<"**"<<std::this_thread::get_id()<<std::endl;
    //this->resource_mutex.unlock();
    return;
}

} // namespace: proj2
