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
        virtual void addReference(ptr *ptr, void *block)
        {
            ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader*>(static_cast<char *>(block) - HEADER_SIZE);
            header->addBlockPtr(ptr);
        }

        virtual bool removeReference(ptr *ptr, void *block)
        {
            assert(block != nullptr);
            ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader*>(static_cast<char *>(block) - HEADER_SIZE);
            header->removeBlockPtr(ptr);
            return !header->hasRef();
        }
        virtual std::list<ptr *> getRefs(void *block)
        {
            ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader*>(static_cast<char *>(block) - HEADER_SIZE);
            return header->getRefs();
        }
    };
}

