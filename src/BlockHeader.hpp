#pragma once

#include <list>
#include "ptr.hpp"
#include "config.hpp"

#define HEADER_SIZE sizeof(ReferenceCountedBlockHeader)

#if ENABLE_EXPERIMENTAL_COMPACTION == 1

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

#else

class ReferenceCountedBlockHeader
{
public:
    ReferenceCountedBlockHeader(size_t size) : size(size) {}
    ~ReferenceCountedBlockHeader() {}
    inline size_t get_size() const { return size; }
    inline bool has_ref() const { return refCount > 0; }
    inline void add_block_ptr(ptr *ptr) { refCount++; }
    inline void remove_block_ptr(ptr *ptr) { refCount--; }
    inline std::list<ptr *> get_references() const { return std::list<ptr *>(); } //Must not be used

private:
    size_t size;
    size_t refCount = 0;
};

#endif // ENABLE_EXPERIMENTAL_COMPACTION