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

        inline void addReference(void *ptr, void *block)
        {
            ptrMap[ptr] = block;
        }

        inline void removeReference(void *ptr)
        {
            ptrMap.erase(ptr);
        }

        inline void *getBlock(void *ptr)
        {
            return ptrMap.at(ptr);
        }

    private:
        std::unordered_map<void *, void *> ptrMap;
    };

}

