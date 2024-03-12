#pragma once
#include <iostream>

namespace MemoryManager
{
    inline void out_of_memory_error()
    {
        std::cerr << "Out of memory" << std::endl;
    }
    inline void throw_invalid_block_error()
    {
        std::cerr << "Invalid block address" << std::endl;
    }

    template <typename T>
    void throw_invalid_index_error(void* ptr, size_t offset)
    {
        size_t blockSize = MemoryManager::Manager::getInstance().get_allocated_block_size(ptr);
        throw std::runtime_error("Invalid block offset " + std::to_string(offset) +
         "(" + std::to_string(offset*sizeof(T)) +" bytes)" + " for block with size " +
          std::to_string(blockSize/sizeof(T)) + "(" + std::to_string(blockSize) + ") bytes.");
    }
}