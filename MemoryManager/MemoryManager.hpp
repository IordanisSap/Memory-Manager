#pragma once

#include <vector>
#include "IMemoryManager.hpp"
#include "BitmapMemoryManager/BitmapMemoryManager.hpp"
#include <stddef.h>
#include <cassert>
#include <iostream>
#include "ReferenceModule/BlockReferenceModule.hpp"
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

    template <typename T>
    void deallocate(T *p)
    {
      if (p == nullptr)
        return;
      p->~T();
      memory_manager->deallocate(p);
    }

    void add_reference(ptr *ptr, void *block)
    {
      if (block == nullptr)
        return;
      if (!memory_manager->is_valid_object(block))
      {
        throw_invalid_block_error();
      }
      ref_module->add_reference(ptr, block);
    }

    void remove_reference(ptr *ptr, void *block)
    {
      if (ptr == nullptr)
        return;
      if (!memory_manager->is_valid_object(block))
      {
        throw_invalid_block_error();
      }
      bool isLastReference = ref_module->remove_reference(ptr, block);
      if (isLastReference)
      {
        memory_manager->deallocate(block);
      }
    }

    bool is_block_offset_valid(void *block, size_t offset)
    {
      return memory_manager->is_valid_object_offset(block, offset);
    }

    size_t get_object_size(void *p)
    {
      return memory_manager->get_object_size(p);
    }

  private:
    static IMemoryManager *memory_manager;
    static IReferenceModule *ref_module;
  };

  extern Manager manager;
  inline IMemoryManager *Manager::memory_manager = nullptr;
  inline IReferenceModule *Manager::ref_module = nullptr;
}
