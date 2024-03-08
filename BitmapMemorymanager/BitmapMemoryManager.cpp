#include "BitmapMemoryManager.hpp"
#include <iostream>
#include <stddef.h>

size_t findIndexForBlockSequence(size_t size, std::vector<bool> &bitmap, size_t start_index);

BitmapMemoryManager::BitmapMemoryManager()
{
    bitmap.resize(NUM_BLOCKS, false);
    arena = new char[NUM_BLOCKS * BLOCK_SIZE];
}

void *BitmapMemoryManager::allocate(size_t size)
{
    size_t i = 0;
    size_t totalSize = size + HEADER_SIZE;

    // Big block
    if (totalSize > BLOCK_SIZE)
    {
        size_t blocksNeeded = totalSize / BLOCK_SIZE + (totalSize % BLOCK_SIZE == 0 ? 0 : 1);
        size_t index = findIndexForBlockSequence(blocksNeeded, bitmap, 0);
        if (index < bitmap.size())
        {
            for (size_t j = index; j < index + blocksNeeded; ++j)
            {
                bitmap[j] = true;
            }
            print_bitmap();
            static_cast<size_t *>(arena)[index * BLOCK_SIZE] = totalSize;
            return static_cast<char *>(arena) + index * BLOCK_SIZE + HEADER_SIZE;
        }
        else
        {
            std::cerr << "Not enough memory" << std::endl;
            return nullptr;
        }
    }

    std::cout << "Allocating " << totalSize << " bytes" << std::endl;

    // Fits in 1 block
    while (i < bitmap.size())
    {
        if (bitmap[i] == false)
        {
            bitmap[i] = true;
            print_bitmap();
            static_cast<size_t *>(arena)[i * BLOCK_SIZE] = totalSize;
            return static_cast<char *>(arena) + i * BLOCK_SIZE + HEADER_SIZE;
        }
        ++i;
    }
    return nullptr;
}

void BitmapMemoryManager::deallocate(void *p)
{
    size_t size = *static_cast<size_t *>(p - HEADER_SIZE);
    char *start = static_cast<char *>(p - HEADER_SIZE);
    size_t index = (start - static_cast<char *>(arena)) / BLOCK_SIZE;

    size_t blocksNeeded = size / BLOCK_SIZE + (size % BLOCK_SIZE == 0 ? 0 : 1);

    std::cout << "Deallocating " << blocksNeeded << " blocks (" << size << " bytes) starting at index " << index << std::endl;

    for (size_t i = index; i < index + blocksNeeded; ++i)
    {
        bitmap[i] = false;
    }
    print_bitmap();
}

void BitmapMemoryManager::print_bitmap() const
{
    for (size_t i = 0; i < bitmap.size(); ++i)
    {
        std::cout << bitmap[i];
    }
    std::cout << std::endl;
}

BitmapMemoryManager::~BitmapMemoryManager()
{
    delete[] static_cast<char *>(arena);
}

size_t findIndexForBlockSequence(size_t size, std::vector<bool> &bitmap, size_t start_index = 0)
{
    size_t i = start_index;
    size_t consecutive = 0;
    while (i < bitmap.size())
    {
        if (bitmap[i] == false)
            consecutive++;
        else
            consecutive = 0;
        if (consecutive == size)
            return i - size + 1;
        i++;
    }
    return SIZE_MAX;
}
