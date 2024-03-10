#ifndef BITMAP_MEMORY_MANAGER_HPP
#define BITMAP_MEMORY_MANAGER_HPP

#define NUM_BLOCKS 32 // Assuming 1024 blocks in the memory pool

#include <vector>
#include "../../include/IMemoryManager.hpp"
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
    virtual bool isAddressValid(void *p);
    void print_bitmap() const;
    inline size_t get_size() const { return size; }

  private:
    bool *bitmap;
    size_t size;
    void *arena;
  };
}

#endif
