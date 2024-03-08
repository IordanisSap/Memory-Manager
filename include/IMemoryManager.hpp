#ifndef IMEMORY_MANAGER_HPP
#define IMEMORY_MANAGER_HPP
#include <stddef.h>

class IMemoryManager
{
public:
    virtual void *allocate(size_t size) = 0;
    virtual void deallocate(void *p) = 0;
    virtual ~IMemoryManager() {};
};

#endif