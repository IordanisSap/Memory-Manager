#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include <vector>
#include "../include/IMemoryManager.hpp"
#include "BitmapMemoryManager/BitmapMemoryManager.hpp"


void* operator new(size_t size);
void* operator new(size_t size, const std::nothrow_t&) noexcept;
void* operator new[](size_t size);
void* operator new[](size_t size, const std::nothrow_t&) noexcept;

void operator delete(void* p);
void operator delete(void*, size_t size);
void operator delete(void*, size_t size, const std::nothrow_t&) noexcept;
void operator delete[](void*, size_t size);
void operator delete[](void* p, size_t size, const std::nothrow_t&) noexcept;
void operator delete[](void* p);



class MemoryManager {
public:
  static MemoryManager& getInstance() {
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
