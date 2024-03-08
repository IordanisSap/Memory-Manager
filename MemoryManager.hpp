#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#define NUM_BLOCKS 16 // Assuming 1024 blocks in the memory pool
#define BLOCK_SIZE 512

#include <vector>
#include "include/IMemoryManager.hpp"
#include "BitmapMemoryManager/BitmapMemoryManager.hpp"


// void* operator new(size_t size);
// void* operator new[](size_t size);

// void operator delete(void* p);
// void operator delete[](void* p);



class MemoryManager {
public:
  static MemoryManager& getInstance() {
    static MemoryManager instance;
    return instance;
  }

  void* allocate(size_t size);
  void deallocate(void* p);

private:
  MemoryManager();
  MemoryManager(const MemoryManager&) = delete;
  MemoryManager& operator=(const MemoryManager&) = delete;
  static MemoryManager instance;
  static IMemoryManager* memory_manager;
};

#endif // MEMORY_MANAGER_HPP
