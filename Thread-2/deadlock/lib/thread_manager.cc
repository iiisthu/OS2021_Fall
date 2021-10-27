#include "thread_manager.h"
#include <iostream>


namespace proj2 {

void ThreadManager::kill(std::thread::id id) {
    /* NOTE: this function does not really kill the thread. This only
             marks the thread as dead. You should call `terminate()`
             explicitly within the thread.
    */
    this->running_status[id] = false;
    this->running_threads[id]->detach();
}

std::thread* ThreadManager::rerun(std::thread::id id) {
    if (this->running_status[id]) {
        // The thread is still running, call kill first or handle error here?
    }
    // The parameters are recorded in the lambda functions, just call it
    return this->new_thread([this, id] {this->functions[id]();});
}

}