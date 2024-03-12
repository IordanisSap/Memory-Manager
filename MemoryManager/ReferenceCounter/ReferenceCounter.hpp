#pragma once

#include <iostream>
#include <unordered_map>

namespace MemoryManager
{
    class ReferenceCounter
    {
    public:
        ReferenceCounter() {}
        ~ReferenceCounter() {}

        void addReference(void *ptr, void *block)
        {
            ptrMap[ptr] = block;
        }

        void removeReference(void *ptr)
        {
            ptrMap.erase(ptr);
        }

        void *getBlock(void *ptr)
        {
            return ptrMap[ptr];
        }

    private:
        std::unordered_map<void *, void *> ptrMap;
    };

}

