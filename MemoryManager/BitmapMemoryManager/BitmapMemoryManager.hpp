#pragma once

#define NUM_BLOCKS 32 // Assuming 1024 blocks in the memory pool

#include <vector>
#include "../IMemoryManager.hpp"
#include <stddef.h>
#include "../Block.hpp"
#include <stdint.h>

namespace BitmapMemoryManager
{
  class MemoryManager : public IMemoryManager
  {
  public:
    MemoryManager();
    ~MemoryManager();
    virtual void *allocate(size_t size);
    virtual void deallocate(void *p);
    virtual bool isBlockValid(void *p) const;
    virtual bool isBlockOffsetValid(void *p, size_t offset) const;
    virtual size_t get_allocated_block_size(void *p) const;
    void print_bitmap() const;
    inline size_t get_size() const { return size; }

  private:
    uint8_t *bitmap;
    size_t size;
    void *arena;
  };
}

