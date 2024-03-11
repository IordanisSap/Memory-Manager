#ifndef IMEMORY_MANAGER_HPP
#define IMEMORY_MANAGER_HPP
#include <stddef.h>

class IMemoryManager
{
public:
    virtual void *allocate(size_t size) = 0;
    virtual void deallocate(void *p) = 0;
    virtual bool isBlockValid(void *p) = 0;
    virtual bool isBlockOffsetValid(void *p, size_t offset) = 0;
    virtual size_t get_allocated_block_size(void *p) = 0;
    virtual ~IMemoryManager() {};
};

#endif