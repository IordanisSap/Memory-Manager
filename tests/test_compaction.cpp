#include "../MemoryManager/GCptr.hpp"
#include "../MemoryManager/MemoryManager.hpp"
#include "test.hpp"
#include <random>
#include <iostream>

#define count 31


void test_small()
{
    MemoryManager::GCptr<int> int1 = MemoryManager::manager.allocate<int>(); 
    MemoryManager::GCptr<int> int2 = MemoryManager::manager.allocate<int>(); 
    MemoryManager::GCptr<int> int3 = MemoryManager::manager.allocate<int>(); 

    int2 = nullptr;
    MemoryManager::GCptr<int> int4 = MemoryManager::manager.allocate<int>(165); 

}

bool test_compaction()
{
    std::mt19937 rng(5);
    std::uniform_int_distribution<int> dist(0, 1); // Range from 1 to 100

    MemoryManager::GCptr<SmallTest> arr[count];
    for (size_t i = 0; i < count; i++)
    {
        arr[i] = MemoryManager::manager.allocate<SmallTest>();
    }
    for (size_t i = 0; i < count; i++)
    {
        if (dist(rng)) arr[i] = nullptr;
    }

    MemoryManager::GCptr<SmallTest> big = MemoryManager::manager.allocate<SmallTest>(300);

    return true;
}
