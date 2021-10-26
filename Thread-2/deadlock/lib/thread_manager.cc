#include "thread_manager.h"


namespace proj2 {

template <class Fn, class... Args>
std::thread* ThreadManager::new_thread(Fn&& fn, Args&&... args) {
    std::thread* th = new std::thread(fn, args...);
    // You can record the status of the thread here for recovery.
    this->running_status[th->get_id()] = true;
}

void ThreadManager::kill(std::thread::id id) {
    /* NOTE: this function does not really kill the thread. This only
             marks the thread as dead. You should call `terminate()`
             explicitly within the thread.
    */
    this->running_status[id] = false;
}

}