#include "MemoryManager.hpp"
#include "BitmapMemoryManager/BitmapMemoryManager.hpp"
#include <iostream>
#include <stddef.h>
#include <cassert>


MemoryManager MemoryManager::instance;
IMemoryManager* MemoryManager::memory_manager = nullptr; // Initialize to nullptr

MemoryManager::MemoryManager()
{
  memory_manager = new BitmapMemoryManager();
}

void* MemoryManager::allocate(size_t size)
{
  return memory_manager->allocate(size);
}

void MemoryManager::deallocate(void* p)
{
  memory_manager->deallocate(p);
}

