#pragma once

#define NUM_BLOCKS 32 // Assuming 1024 blocks in the memory pool

#include <vector>
#include "../IMemoryManager.hpp"
#include <stddef.h>
#include "../Block.hpp"

namespace BitmapMemoryManager
{
  class MemoryManager : public IMemoryManager
  {
  public:
    MemoryManager();
    ~MemoryManager();
    virtual void *allocate(size_t size);
    virtual void deallocate(void *p);
    virtual bool isBlockValid(void *p);
    virtual bool isBlockOffsetValid(void *p, size_t offset);
    virtual size_t get_allocated_block_size(void *p);
    void print_bitmap() const;
    inline size_t get_size() const { return size; }

  private:
    bool *bitmap;
    size_t size;
    void *arena;
  };
}

