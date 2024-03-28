#pragma once

#include <list>
#include "ptr/ptr.hpp"
#include "CustomAllocator/CustomAllocator.hpp"

#define HEADER_SIZE sizeof(ReferenceCountedBlockHeader)

class ReferenceCountedBlockHeader
{
public:
    ReferenceCountedBlockHeader(size_t size) : size(size) {}
    ~ReferenceCountedBlockHeader() {}
    inline size_t get_size() const { return size; }
    inline bool has_ref() const { return !refs.empty(); }
    inline void add_block_ptr(ptr *ptr) { refs.push_front(ptr); }
    inline void remove_block_ptr(ptr *ptr) { refs.remove(ptr); }
    inline std::list<ptr *> get_references() const { return refs; }

private:
    size_t size;
    std::list<ptr *> refs;
};
