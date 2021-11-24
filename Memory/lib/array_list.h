#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cstdlib>

namespace proj3 {

    class MemoryManager;

    class ArrayList{
        private:
        friend class MemoryManager;
        size_t size;
        MemoryManager* mma;
        int array_id;
        ArrayList(size_t, MemoryManager*, int);
        ~ArrayList();
        public:
        // you should not modify the public interfaces used in tests
        int Read (unsigned long);
        void Write (unsigned long, int);
    };

} // namespce: proj3
#endif