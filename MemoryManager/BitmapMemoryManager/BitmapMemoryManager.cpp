#include "BitmapMemoryManager.hpp"
#include <iostream>
#include <stddef.h>
#include <cstdint>
#include <cstring>
#include "../BlockHeader.hpp"
#include <cmath>
#include "stdint.h"
#include "../Errors.hpp"

#include <bit>

#define LOGGING false
#define get_num_of_set_bits(byte) std::popcount(byte)
#define get_num_of_consecutive_zero_bits(byte) std::countr_zero(byte)

size_t find_index_for_block_sequence(size_t size, uint8_t *&bitmap, size_t bitmapSize);

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
        bitmap = new uint8_t[this->size / 8 + (this->size % 8 != 0)];
        for (size_t i = 0; i < this->size; ++i)
        {
            set_bit(bitmap, i, false);
        }
        arena = new std::byte[this->size * this->block_size];
    }

    void *MemoryManager::allocate(size_t size)
    {
        size_t i = 0;
        size_t totalSize = size + HEADER_SIZE;

        if (totalSize > this->block_size)
        {
            size_t blocksNeeded = totalSize / this->block_size + (totalSize % this->block_size == 0 ? 0 : 1);
            size_t index = find_index_for_block_sequence(blocksNeeded, bitmap, this->get_size());
            if (index < this->get_size())
            {
                for (size_t j = index; j < index + blocksNeeded; ++j)
                {
                    set_bit(bitmap, j, true);
                }
                print_bitmap();
                size_t byteOffset = index * this->block_size;
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
            // auto tmp = get_num_of_set_bits(bitmap[i]);
            if (get_num_of_set_bits(bitmap[i]) == 8)
            {
                i += 8;
                continue;
            }
            while (get_bit(bitmap, i))
            {
                ++i;
            }
            set_bit(bitmap, i, true);
            print_bitmap();
            new (arena + i * this->block_size) ReferenceCountedBlockHeader(totalSize);
            return arena + i * this->block_size + HEADER_SIZE;
        }
        return nullptr;
    }

    void MemoryManager::deallocate(void *p)
    {
        std::byte *block_start = static_cast<std::byte *>(p) - HEADER_SIZE;
        ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader *>(block_start);
        size_t size = header->get_size();
        size_t index = (block_start - arena) / this->block_size;

        size_t blocksNeeded = size / this->block_size + (size % this->block_size == 0 ? 0 : 1);

        for (size_t i = index; i < index + blocksNeeded; ++i)
        {
            set_bit(bitmap, i, false);
        }
        print_bitmap();
    }

    bool MemoryManager::is_valid_object(void *p) const
    {
        return true;
        return p >= arena && p < arena + this->get_size() * this->block_size;
    }

    bool MemoryManager::is_valid_object_offset(void *p, size_t offset) const
    {
        return is_valid_object(p) && reinterpret_cast<ReferenceCountedBlockHeader *>(static_cast<std::byte *>(p) - HEADER_SIZE)->get_size() - HEADER_SIZE > offset;
    }

    size_t MemoryManager::get_object_size(void *p) const
    {
        if (!is_valid_object(p))
        {
            throw_invalid_block_error();
        }
        ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader *>(static_cast<std::byte *>(p) - HEADER_SIZE);
        return header->get_size() - HEADER_SIZE;
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
            if (pos != arena + i * this->block_size)
            {
                ReferenceCountedBlockHeader *header = reinterpret_cast<ReferenceCountedBlockHeader *>(arena + i * this->block_size);
                size_t size = header->get_size();
                auto references = header->get_references();

                *reinterpret_cast<ReferenceCountedBlockHeader *>(pos) = std::move(*header);

                for (auto &ref : references)
                {
                    ref->block = pos + HEADER_SIZE;
                }
                // Set new used bits to 1 and remaining old bits to 0
                size_t blocksNeeded = size / this->block_size + (size % this->block_size == 0 ? 0 : 1);
                size_t startIndex = (pos - arena) / this->block_size;
                for (size_t j = startIndex; j < startIndex + blocksNeeded; ++j)
                {
                    set_bit(bitmap, j, true);
                }
                for (size_t j = i; j < i + blocksNeeded; ++j)
                {
                    set_bit(bitmap, j, false);
                }
                pos += blocksNeeded * this->block_size;
                i += blocksNeeded;
                if (LOGGING)
                    print_bitmap();
                continue;
            }
            pos += this->block_size;
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
size_t find_index_for_block_sequence(size_t size, uint8_t *&bitmap, size_t bitmapSize)
{
    size_t i = 0;
    size_t consecutive = 0;
    while (i < bitmapSize - 7)
    {
        if (get_num_of_consecutive_zero_bits(bitmap[i]) < size - consecutive && get_bit(bitmap, i + 7))
        { // Not enough consecutive zeros in the byte and last byte is not empty, so it cant be connected to the next byte
            i += 8;
            consecutive = 0;
            continue;
        }
        if (!get_bit(bitmap, i))
            consecutive++;
        else
            consecutive = 0;
        if (consecutive == size)
            return i - size + 1;
        i++;
    }
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
