#pragma once

#include <list>
#include "ptr.hpp"

#define BLOCK_SIZE 512
#define HEADER_SIZE sizeof(ReferenceCountedBlockHeader)

class ReferenceCountedBlockHeader
{
public:
    ReferenceCountedBlockHeader(size_t size) : size(size){}
    ~ReferenceCountedBlockHeader() {}
    inline size_t getSize() const {return size;}
    inline bool hasRef() const {return !refs.empty();}
    inline ptr *getBlockPtr() const {return refs.front();}
    inline void addBlockPtr(ptr *ptr) {refs.push_front(ptr);}
    inline void removeBlockPtr(ptr *ptr) {refs.remove(ptr);}
    inline std::list<ptr *> getRefs() const {return refs;}

private:
    size_t size;
    std::list<ptr *> refs;
};
