#pragma once

#include <stddef.h>

class IMemoryAllocator
{
public:
    virtual void *allocate(size_t size) = 0;
    virtual void deallocate(void *p) = 0;
    virtual bool is_valid_object(void *p) const = 0;
    virtual bool is_valid_object_offset(void *p, size_t offset) const = 0;
    virtual void *compact() = 0;
    virtual size_t get_object_size(void *p) const = 0;
    virtual ~IMemoryAllocator() {};
};

