#include "MemoryManager.hpp"
#include "BitmapMemoryManager/BitmapMemoryManager.hpp"
#include <iostream>
#include <stddef.h>
#include <cassert>


MemoryManager MemoryManager::instance;
IMemoryManager* MemoryManager::memory_manager = nullptr; // Initialize to nullptr

void* operator new(size_t size)
{
  return MemoryManager::getInstance().allocate(size);
}

void operator delete(void* p)
{
  MemoryManager::getInstance().deallocate(p);
}


MemoryManager::MemoryManager()
{
  memory_manager = (IMemoryManager*) malloc(sizeof(BitmapMemoryManager));
  memory_manager = new (memory_manager) BitmapMemoryManager();
}

void* MemoryManager::allocate(size_t size)
{
  return memory_manager->allocate(size);
}

void MemoryManager::deallocate(void* p)
{
  memory_manager->deallocate(p);
}

