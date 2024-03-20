#pragma once

#include "../Block.hpp"
#include <iostream>
#include "ReferenceCounter.hpp"
#include <cassert>

namespace MemoryManager
{
    class BlockReferenceCounter
    {
    public:
        BlockReferenceCounter() {}
        ~BlockReferenceCounter() {}

        void addReference(void *ptr, void *block)
        {
            //reference_counter.addReference(ptr, block);
            ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader*>(static_cast<char *>(block) - HEADER_SIZE);
            header->incrementRef();
        }

        bool removeReference(void *block)
        {
            assert(block != nullptr);
            ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader*>(static_cast<char *>(block) - HEADER_SIZE);
            header->decrementRef();
            if (header->getRefCount() == 0)
            {
                //std::cout << "Deallocating block at address: " << block << std::endl;
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

