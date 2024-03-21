#include "../MemoryManager/GCptr.hpp"
#include "../MemoryManager/MemoryManager.hpp"
#include "test.hpp"
#include <random>
#include <iostream>
#include <chrono>

#include <bit>

#define test_count 1020

void test_small()
{
    MemoryManager::GCptr<int> int1 = MemoryManager::manager.allocate<int>();
    MemoryManager::GCptr<int> int2 = MemoryManager::manager.allocate<int>();
    MemoryManager::GCptr<int> int3 = MemoryManager::manager.allocate<int>();

    int2 = nullptr;
    MemoryManager::GCptr<int> int4 = MemoryManager::manager.allocate<int>(165);
}

using namespace std::chrono;

void test_normal()
{
    std::mt19937 rng(5);
    std::uniform_int_distribution<int> dist(0, 1); // Range from 1 to 100

    auto start = high_resolution_clock::now();

    for (size_t i = 0; i < 100; i++)
    {
        MemoryManager::GCptr<SmallTest> arr[test_count];
        for (size_t i = 0; i < test_count; i++)
        {
            arr[i] = MemoryManager::manager.allocate<SmallTest>();
        }
        // exit(0);
        for (size_t i = 0; i < test_count; i++)
        {
            if (dist(rng))
                arr[i] = nullptr;
        }

        // MemoryManager::GCptr<SmallTest> big = MemoryManager::manager.allocate<SmallTest>(800);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Custom malloc time: " << duration.count() << " microseconds" << std::endl;
}

void test_normal2()
{
    std::mt19937 rng(5);
    std::uniform_int_distribution<int> dist(0, 1); // Range from 1 to 100

    auto start = high_resolution_clock::now();


    for (size_t i = 0; i < 1; i++)
    {
        SmallTest *arr[test_count];
        for (size_t i = 0; i < test_count; i++)
        {
            arr[i] = new SmallTest();
        }
        for (size_t i = 0; i < test_count; i++)
        {
            if (dist(rng))
                delete arr[i];
        }

        SmallTest *big = new SmallTest[800];
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Custom malloc time: " << duration.count() << " microseconds" << std::endl;
}

bool test_compaction()
{
    test_normal();
    //test_normal2();
    return true;
}
