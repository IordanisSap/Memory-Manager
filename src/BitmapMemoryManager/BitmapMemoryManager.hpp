#pragma once

#include <vector>
#include "../IMemoryManager.hpp"
#include <stddef.h>
#include "../BlockHeader.hpp"
#include <stdint.h>
#include <cstddef>
#include "config.hpp"

namespace BitmapMemoryManager
{
  class MemoryManager : public IMemoryManager
  {
  public:
    MemoryManager();
    ~MemoryManager();
    virtual void *allocate(size_t size);
    virtual void deallocate(void *p);
    virtual bool is_valid_object(void *p) const;
    virtual bool is_valid_object_offset(void *p, size_t offset) const;
    virtual size_t get_object_size(void *p) const;
    virtual void *compact();
    void print_bitmap() const;
    inline size_t get_size() const { return size; }

  private:
    uint8_t *bitmap;
    size_t size = BLOCK_NUM;
    size_t block_size = BLOCK_SIZE;
    std::byte *arena;
  };
}
