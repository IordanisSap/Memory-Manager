#include "BitmapMemoryManager.hpp"
#include <iostream>
#include <stddef.h>
#include <cstdint>
#include <cstring>
#include "../Block.hpp"
#include <cmath>
#include "stdint.h"
#include "../Errors.hpp"

size_t findIndexForBlockSequence(size_t size, uint8_t *&bitmap, size_t bitmapSize);

void set_bit(uint8_t *bitmap, size_t index, bool value)
{
    size_t byteIndex = index / 8;
    size_t bitIndex = index % 8;
    if (value)
    {
        bitmap[byteIndex] |= 1 << bitIndex;
    }
    else
    {
        bitmap[byteIndex] &= ~(1 << bitIndex);
    }
}

bool get_bit(uint8_t *bitmap, size_t index)
{
    size_t byteIndex = index / 8;
    size_t bitIndex = index % 8;
    return (bitmap[byteIndex] >> bitIndex) & 1;
}

namespace BitmapMemoryManager
{
    MemoryManager::MemoryManager()
    {
        this->size = NUM_BLOCKS;
        bitmap = new uint8_t[this->size/8 + (this->size % 8 != 0)];
        for (size_t i = 0; i < this->size; ++i)
        {
            set_bit(bitmap, i, false);
        }
        arena = new uint8_t[this->size * BLOCK_SIZE];
    }

    void *MemoryManager::allocate(size_t size)
    {
        size_t i = 0;
        size_t totalSize = size + HEADER_SIZE;

        if (totalSize > BLOCK_SIZE)
        {
            size_t blocksNeeded = totalSize / BLOCK_SIZE + (totalSize % BLOCK_SIZE == 0 ? 0 : 1);
            size_t index = findIndexForBlockSequence(blocksNeeded, bitmap, this->get_size());
            if (index < this->get_size())
            {
                for (size_t j = index; j < index + blocksNeeded; ++j)
                {
                    set_bit(bitmap, j, true);
                }
                print_bitmap();
                size_t byteOffset = index * BLOCK_SIZE;
                new (static_cast<uint8_t *>(arena) + byteOffset) ReferenceCountedBlockHeader(totalSize);
                return static_cast<uint8_t *>(arena) + byteOffset + HEADER_SIZE;
            }
            else
            {
                std::cerr << "Not enough memory" << std::endl;
                return nullptr;
            }
        }

        // Fits in 1 block
        while (i < this->get_size())
        {
            if (!get_bit(bitmap, i))
            {
                set_bit(bitmap, i, true);
                print_bitmap();
                new (static_cast<uint8_t *>(arena) + i * BLOCK_SIZE) ReferenceCountedBlockHeader(totalSize);
                return static_cast<uint8_t *>(arena) + i * BLOCK_SIZE + HEADER_SIZE;
            }
            ++i;
        }
        return nullptr;
    }

    void MemoryManager::deallocate(void *p)
    {
        uint8_t *block_start = static_cast<uint8_t *>(p) - HEADER_SIZE;
        ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader *>(block_start);
        size_t size = header->getSize();
        size_t index = (block_start - static_cast<uint8_t *>(arena)) / BLOCK_SIZE;

        size_t blocksNeeded = size / BLOCK_SIZE + (size % BLOCK_SIZE == 0 ? 0 : 1);

        for (size_t i = index; i < index + blocksNeeded; ++i)
        {
            set_bit(bitmap, i, false);
        }
        print_bitmap();
    }

    bool MemoryManager::isBlockValid(void *p) const
    {
        return true;
        return p >= arena && p < static_cast<uint8_t *>(arena) + this->get_size() * BLOCK_SIZE;
    }

    bool MemoryManager::isBlockOffsetValid(void *p, size_t offset) const
    {
        return isBlockValid(static_cast<uint8_t *>(p)) && reinterpret_cast<ReferenceCountedBlockHeader *>(static_cast<uint8_t *>(p) - HEADER_SIZE)->getSize() - HEADER_SIZE > offset;
    }

    size_t MemoryManager::get_allocated_block_size(void *p) const
    {
        if (!isBlockValid(p)){
            throw_invalid_block_error();
        }
        ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader *>(static_cast<uint8_t *>(p) - HEADER_SIZE);
        return header->getSize() - HEADER_SIZE;
    }

    void MemoryManager::print_bitmap() const
    {
        return;
        for (size_t i = 0; i < this->get_size(); ++i)
        {
            std::cout << get_bit(bitmap, i);
        }
        std::cout << std::endl;
    }

    MemoryManager::~MemoryManager()
    {
        delete[] static_cast<uint8_t *>(arena);
    }
}
size_t findIndexForBlockSequence(size_t size, uint8_t *&bitmap, size_t bitmapSize)
{
    size_t i = 0;
    size_t consecutive = 0;
    while (i < bitmapSize)
    {
        if (!get_bit(bitmap, i))
            consecutive++;
        else
            consecutive = 0;
        if (consecutive == size)
            return i - size + 1;
        i++;
    }
    return SIZE_MAX;
}
