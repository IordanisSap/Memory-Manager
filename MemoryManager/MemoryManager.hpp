#pragma once

#include <vector>
#include "../include/IMemoryManager.hpp"
#include "BitmapMemoryManager/BitmapMemoryManager.hpp"
#include <stddef.h>
#include <cassert>
#include <iostream>
#include "ReferenceCounter/BlockReferenceCounter.hpp"

namespace MemoryManager
{
  class Manager
  {
  public:
    static Manager &getInstance()
    {
      return instance;
    }

    template <typename T>
    T *allocate(size_t size)
    {
      void *ptr = memory_manager->allocate(size * sizeof(T));
      for (size_t i = 0; i < size; ++i)
      {
        new (static_cast<T *>(ptr) + i) T();
      }
      return static_cast<T *>(ptr);
    }

    template <typename T>
    T *allocate()
    {
      void *ptr = memory_manager->allocate(sizeof(T));
      new (ptr) T();
      return static_cast<T *>(ptr);
    }

    void deallocate(void *p)
    {
    }

    void addReference(void *ptr, void *block)
    {
      if (block == nullptr) return;
      if (!memory_manager->isBlockValid(block)){
        std::cout << "Invalid block address" << std::endl;
        return;
      }
      reference_counter->addReference(ptr, block);
    }

    void removeReference(void *ptr, void* block)
    {
      if (ptr == nullptr) return;
      if (!memory_manager->isBlockValid(block)){
        std::cout << "Invalid block address" << std::endl;
        return;
      }
      bool isLastReference = reference_counter->removeReference(ptr);
      if (isLastReference)
      {
        memory_manager->deallocate(block);
      }
    }

    bool isBlockOffsetValid(void *block, size_t offset)
    {
      return memory_manager->isBlockOffsetValid(block, offset);
    }

    size_t get_allocated_block_size(void *p)
    {
      return memory_manager->get_allocated_block_size(p);
    }

  private:
    Manager()
    {
      memory_manager = new BitmapMemoryManager::MemoryManager();
      reference_counter = new BlockReferenceCounter();
    }
    Manager(const Manager &) = delete;
    Manager &operator=(const Manager &) = delete;
    static Manager instance;
    static IMemoryManager *memory_manager;
    static BlockReferenceCounter *reference_counter;
  };


  inline Manager Manager::instance;
  inline IMemoryManager *Manager::memory_manager = nullptr;
  inline BlockReferenceCounter *Manager::reference_counter = nullptr;
}
