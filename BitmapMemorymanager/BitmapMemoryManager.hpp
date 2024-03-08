#ifndef BITMAP_MEMORY_MANAGER_HPP
#define BITMAP_MEMORY_MANAGER_HPP

#define NUM_BLOCKS 1024 // Assuming 1024 blocks in the memory pool
#define BLOCK_SIZE 512
#define HEADER_SIZE sizeof(size_t)

#include <vector>
#include "../include/IMemoryManager.hpp"


class BitmapMemoryManager : public IMemoryManager
{
public:
    BitmapMemoryManager();
    ~BitmapMemoryManager();
    virtual void* allocate(size_t size);
    virtual void deallocate(void* p);
    void print_bitmap() const;  
    inline size_t get_size() const { return size; }

  private:
    bool* bitmap;
    size_t size;
    void* arena;
};

#endif
