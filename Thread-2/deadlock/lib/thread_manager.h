#ifndef DEADLOCK_LIB_THREAD_MANAGER_H_
#define DEADLOCK_LIB_THREAD_MANAGER_H_

#include <map>
#include <thread>
#include <functional>

namespace proj2 {

// NOTE: ThreadManager is not thread-safe.
class ThreadManager {
public:
    ThreadManager() {}
    void kill(std::thread::id);
    std::thread* rerun(std::thread::id);
    template <class Fn, class... Args>
    std::thread* new_thread(Fn&& fn, Args&&... args);
    bool is_killed(std::thread::id id) { return !running_status[id]; }
private:
    std::map<std::thread::id, bool> running_status;
    std::map<std::thread::id, std::thread*> running_threads;
    std::map<std::thread::id, std::function<void()> > functions; 
};

template <class Fn, class... Args>
std::thread* ThreadManager::new_thread(Fn&& fn, Args&&... args) {
    std::thread* th = new std::thread(fn, args...);

    // Record this thread
    this->running_status[th->get_id()] = true;
    // Record this thread's running arguments for restart
    this->functions[th->get_id()] = [fn, args...] { (fn)(args...); };
    // Record this thread's pointer for further detach
    this->running_threads[th->get_id()] = th;

    // NOTE: You can record more information of the thread here if needed.

    return th;
}

}  // namespce: proj2

#endif