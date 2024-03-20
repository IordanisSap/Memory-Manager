#pragma once

#define BLOCK_SIZE 512
#define BLOCK_SIZE_OFFSET 0
#define BLOCK_PTR_COUNT_OFFSET 4
#define HEADER_SIZE sizeof(ReferenceCountedBlockHeader)

class ReferenceCountedBlockHeader
{
public:
    ReferenceCountedBlockHeader(size_t size) : size(size), refCount(0) {}
    ~ReferenceCountedBlockHeader() {}
    inline void incrementRef() {this->refCount += 1;}
    inline bool decrementRef(){return --this->refCount == 0;}
    inline size_t getSize() const {return size;}
    inline size_t getRefCount() const {return refCount;}
private:
    size_t size;
    size_t refCount;
};
