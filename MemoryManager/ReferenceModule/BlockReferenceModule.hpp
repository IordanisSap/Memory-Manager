#pragma once

#include "../BlockHeader.hpp"
#include <iostream>
#include "IReferenceModule.hpp"
#include <cassert>

namespace MemoryManager
{
    class BlockReferenceModule : public IReferenceModule
    {
    public:
        virtual void add_reference(ptr *ptr, void *block)
        {
            ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader*>(static_cast<char *>(block) - HEADER_SIZE);
            header->add_block_ptr(ptr);
        }

        virtual bool remove_reference(ptr *ptr, void *block)
        {
            assert(block != nullptr);
            ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader*>(static_cast<char *>(block) - HEADER_SIZE);
            header->remove_block_ptr(ptr);
            return !header->has_ref();
        }
        virtual std::list<ptr *> get_references(void *block)
        {
            ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader*>(static_cast<char *>(block) - HEADER_SIZE);
            return header->get_references();
        }
    };
}

