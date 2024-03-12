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
    void incrementRef() {this->refCount += 1;}
    bool decrementRef(){return --this->refCount == 0;}
    size_t getSize() const {return size;}
    size_t getRefCount() const {return refCount;}
private:
    size_t size;
    size_t refCount;
};
