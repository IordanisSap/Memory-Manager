#include "BitmapMemoryManager.hpp"
#include <iostream>
#include <stddef.h>
#include <cstdint>
#include <cstring>

size_t findIndexForBlockSequence(size_t size, bool* &bitmap, size_t bitmapSize);

BitmapMemoryManager::BitmapMemoryManager()
{
    this->size = NUM_BLOCKS;
    bitmap = (bool*)malloc(NUM_BLOCKS * sizeof(bool));
    for (size_t i = 0; i < NUM_BLOCKS; ++i)
    {
        bitmap[i] = false;
    }
    arena = malloc(NUM_BLOCKS * BLOCK_SIZE);
}

void *BitmapMemoryManager::allocate(size_t size)
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
                bitmap[j] = true;
            }
            std::memcpy(static_cast<char *>(arena) + index * BLOCK_SIZE, &totalSize, sizeof(size_t));
            return static_cast<char *>(arena) + index * BLOCK_SIZE + HEADER_SIZE;
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
        if (bitmap[i] == false)
        {
            bitmap[i] = true;
            std::memcpy(static_cast<char *>(arena) + i * BLOCK_SIZE, &totalSize, sizeof(size_t));
            return static_cast<char *>(arena) + i * BLOCK_SIZE + HEADER_SIZE;
        }
        ++i;
    }
    return nullptr;
}

void BitmapMemoryManager::deallocate(void *p)
{
    size_t size = *reinterpret_cast<size_t *>(static_cast<char *>(p) - HEADER_SIZE);
    char *start = static_cast<char *>(static_cast<char *>(p) - HEADER_SIZE);
    size_t index = (start - static_cast<char *>(arena)) / BLOCK_SIZE;

    size_t blocksNeeded = size / BLOCK_SIZE + (size % BLOCK_SIZE == 0 ? 0 : 1);


    for (size_t i = index; i < index + blocksNeeded; ++i)
    {
        bitmap[i] = false;
    }
}

void BitmapMemoryManager::print_bitmap() const
{
    for (size_t i = 0; i < this->get_size(); ++i)
    {
        std::cout << bitmap[i];
    }
    std::cout << std::endl;
}

BitmapMemoryManager::~BitmapMemoryManager()
{
    delete[] static_cast<char *>(arena);
}

size_t findIndexForBlockSequence(size_t size, bool* &bitmap, size_t bitmapSize)
{
    size_t i = 0;
    size_t consecutive = 0;
    while (i < bitmapSize)
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
