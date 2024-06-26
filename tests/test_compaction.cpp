#include "GCptr.hpp"
#include "MemoryManager.hpp"
#include "test.hpp"
#include <random>
#include <iostream>
#include <chrono>
#include "config.hpp"

#include <bit>

#define test_count BLOCK_NUM

using namespace std::chrono;

void test_allocator()
{
    std::mt19937 rng(5);
    std::uniform_int_distribution<int> dist(0, 1); // Range from 1 to 100

    auto start = high_resolution_clock::now();

    MemoryManager::GCptr<SmallTest> arr[test_count];
    for (size_t i = 0; i < test_count; i++)
    {
        arr[i] = MemoryManager::manager.allocate<SmallTest>();
    }
    for (size_t i = 0; i < test_count; i++)
    {
        if (dist(rng))
            arr[i] = nullptr;
    }
    MemoryManager::GCptr<SmallTest> big = MemoryManager::manager.allocate<SmallTest>(400);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Custom allocator time: " << duration.count() << " microseconds" << std::endl;
}

void test_normal()
{
    std::mt19937 rng(5);
    std::uniform_int_distribution<int> dist(0, 1); // Range from 1 to 100

    auto start = high_resolution_clock::now();

    SmallTest *arr[test_count];
    for (size_t i = 0; i < test_count; i++)
    {
        arr[i] = new SmallTest();
    }
    for (size_t i = 0; i < test_count; i++)
    {
        if (dist(rng))
        {
            delete arr[i];
            arr[i] = nullptr;
        }
        else
        {
            delete arr[i];
        }
    }
    SmallTest *big = new SmallTest[800];
    delete[] big;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "alloc time: " << duration.count() << " microseconds" << std::endl;
}

bool test_compaction()
{
    std::cout << "----------Running compaction tests----------" << std::endl;
    test_allocator();
    test_normal();
    return true;
}
