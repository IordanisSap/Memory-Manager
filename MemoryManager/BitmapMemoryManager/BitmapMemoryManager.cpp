#include "BitmapMemoryManager.hpp"
#include <iostream>
#include <stddef.h>
#include <cstdint>
#include <cstring>
#include "../Block.hpp"
#include <cmath>
#include "stdint.h"
#include "../Errors.hpp"

#include <bit>

#define LOGGING false
#define get_num_of_set_bits(byte) 

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


inline unsigned char num_of_nonzero_bits(uint8_t byte)
{
    unsigned char count = 0;
    while (byte)
    {
        count += byte & 1;
        byte >>= 1;
    }
    return count;
}

namespace BitmapMemoryManager
{
    MemoryManager::MemoryManager()
    {
        this->size = NUM_BLOCKS;
        bitmap = new uint8_t[this->size / 8 + (this->size % 8 != 0)];
        for (size_t i = 0; i < this->size; ++i)
        {
            set_bit(bitmap, i, false);
        }
        arena = new std::byte[this->size * BLOCK_SIZE];
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
                new (arena + byteOffset) ReferenceCountedBlockHeader(totalSize);
                return arena + byteOffset + HEADER_SIZE;
            }
            else
            {
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
                new (arena + i * BLOCK_SIZE) ReferenceCountedBlockHeader(totalSize);
                return arena + i * BLOCK_SIZE + HEADER_SIZE;
            }
            ++i;
        }
        return nullptr;
    }

    void MemoryManager::deallocate(void *p)
    {
        std::byte *block_start = static_cast<std::byte *>(p) - HEADER_SIZE;
        ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader *>(block_start);
        size_t size = header->getSize();
        size_t index = (block_start - arena) / BLOCK_SIZE;

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
        return p >= arena && p < arena + this->get_size() * BLOCK_SIZE;
    }

    bool MemoryManager::isBlockOffsetValid(void *p, size_t offset) const
    {
        return isBlockValid(p) && reinterpret_cast<ReferenceCountedBlockHeader *>(static_cast<std::byte *>(p) - HEADER_SIZE)->getSize() - HEADER_SIZE > offset;
    }

    size_t MemoryManager::get_allocated_block_size(void *p) const
    {
        if (!isBlockValid(p))
        {
            throw_invalid_block_error();
        }
        ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader *>(static_cast<std::byte *>(p) - HEADER_SIZE);
        return header->getSize() - HEADER_SIZE;
    }

    void *MemoryManager::compact()
    {
        size_t i = 0;
        std::byte *pos = arena;
        size_t arenaBlockSize = this->get_size();
        while (i < arenaBlockSize)
        {
            if (!get_bit(bitmap, i))
            {
                ++i;
                continue;
            }
            if (pos != arena + i * BLOCK_SIZE)
            {
                ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader *>(arena + i * BLOCK_SIZE);
                size_t size = header->getSize();
                std::list<ptr *> references = header->getRefs();
                
                *reinterpret_cast<ReferenceCountedBlockHeader *>(pos) = std::move(*header);
                

                for (auto& ref : references)
                {
                    ref->block = pos + HEADER_SIZE;
                }
                // Set new used bits to 1 and remaining old bits to 0
                size_t blocksNeeded = size / BLOCK_SIZE + (size % BLOCK_SIZE == 0 ? 0 : 1);
                size_t startIndex = (pos - arena) / BLOCK_SIZE;
                for (size_t j = startIndex; j < startIndex + blocksNeeded; ++j)
                {
                    set_bit(bitmap, j, true);
                }
                for (size_t j = i; j < i + blocksNeeded; ++j)
                {
                    set_bit(bitmap, j, false);
                }
                pos += blocksNeeded * BLOCK_SIZE;
                i += blocksNeeded;
                if (LOGGING) print_bitmap();
                continue;
            }
            pos += BLOCK_SIZE;
            i++;
        }
        return arena;
    }

    void MemoryManager::print_bitmap() const
    {
        if (!LOGGING)
            return;
        for (size_t i = 0; i < this->get_size(); ++i)
        {
            std::cout << get_bit(bitmap, i);
        }
        std::cout << std::endl;
    }

    MemoryManager::~MemoryManager()
    {
        delete[] (arena);
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
