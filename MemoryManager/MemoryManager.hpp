#pragma once

#include <vector>
#include "IMemoryManager.hpp"
#include "BitmapMemoryManager/BitmapMemoryManager.hpp"
#include <stddef.h>
#include <cassert>
#include <iostream>
#include "ReferenceCounter/BlockReferenceModule.hpp"
#include "Errors.hpp"

namespace MemoryManager
{
  class Manager
  {
  public:
    Manager()
    {
      memory_manager = new BitmapMemoryManager::MemoryManager();
      ref_module = new BlockReferenceModule();
    }

    template <typename T>
    T *allocate(size_t size)
    {
      void *ptr = memory_manager->allocate(size * sizeof(T));
      if (ptr == nullptr)
      {
        memory_manager->compact();
        ptr = memory_manager->allocate(size * sizeof(T));
      }
      if (ptr == nullptr)
        throw_out_of_memory_error();
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
      if (ptr == nullptr)
      {
        memory_manager->compact();
        ptr = memory_manager->allocate(sizeof(T));
      }
      if (ptr == nullptr)
        throw_out_of_memory_error();
      new (ptr) T();
      return static_cast<T *>(ptr);
    }

    void addReference(ptr *ptr, void *block)
    {
      if (block == nullptr)
        return;
      if (!memory_manager->isBlockValid(block))
      {
        throw_invalid_block_error();
      }
      ref_module->addReference(ptr, block);
    }

    void removeReference(ptr *ptr, void *block)
    {
      if (ptr == nullptr)
        return;
      if (!memory_manager->isBlockValid(block))
      {
        throw_invalid_block_error();
      }
      bool isLastReference = ref_module->removeReference(ptr, block);
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
    static IMemoryManager *memory_manager;
    static BlockReferenceModule *ref_module;
  };

  extern Manager manager;
  inline IMemoryManager *Manager::memory_manager = nullptr;
  inline BlockReferenceModule *Manager::ref_module = nullptr;
}
