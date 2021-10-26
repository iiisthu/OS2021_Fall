#ifndef DEADLOCK_LIB_THREAD_MANAGER_H_
#define DEADLOCK_LIB_THREAD_MANAGER_H_

#include <map>
#include <thread>

namespace proj2 {

class ThreadManager {
public:
    void kill(std::thread::id id);
    template <class Fn, class... Args>
    std::thread* new_thread(Fn&& fn, Args&&... args);
private:
    std::map<std::thread::id, bool> running_status;
};

}  // namespce: proj2

#endif