#ifndef BLOCK_REFERENCECOUNTER_HPP
#define BLOCK_REFERENCECOUNTER_HPP

#include "../Block.hpp"
#include <iostream>
#include "ReferenceCounter.hpp"

namespace MemoryManager
{
    class BlockReferenceCounter
    {
    public:
        BlockReferenceCounter() {}
        ~BlockReferenceCounter() {}

        void addReference(void *ptr, void *block)
        {
            reference_counter.addReference(ptr, block);
            *reinterpret_cast<size_t*>(static_cast<char*>(block) - HEADER_SIZE + BLOCK_PTR_COUNT_OFFSET) += 1;
        }

        bool removeReference(void *ptr)
        {
            void *block = reference_counter.getBlock(ptr);
            size_t* ptr_count = reinterpret_cast<size_t*>(static_cast<char*>(block) - HEADER_SIZE + BLOCK_PTR_COUNT_OFFSET);
            reference_counter.removeReference(ptr);
            *ptr_count -= 1;
            if (*ptr_count == 0)
            {
                std::cout << "Deallocating block at address: " << block << std::endl;
                return true;
            }
            return false;
        }

        void *getBlock(void *ptr)
        {
            return reference_counter.getBlock(ptr);
        }

    private:
        ReferenceCounter reference_counter;
    };

}

#endif