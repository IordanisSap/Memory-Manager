#include <chrono>
#include "test.hpp"
#include "../MemoryManager/MemoryManager.hpp"
#include "../MemoryManager/ptr/GCptr.hpp"

using namespace std::chrono;

#define MALLOC_TEST_COUNT 100000


void test_custom_allocator()
{
    auto start = high_resolution_clock::now();

    for (size_t i = 0; i < MALLOC_TEST_COUNT; i++)
    {
        MemoryManager::GCptr<SmallTest> t1 = MemoryManager::manager.allocate<SmallTest>();
        MemoryManager::GCptr<SmallTest> t2 = MemoryManager::manager.allocate<SmallTest>();
        MemoryManager::GCptr<SmallTest> t3 = MemoryManager::manager.allocate<SmallTest>();
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Custom allocator time: " << duration.count() << " microseconds" << std::endl;
}

void test_custom_allocator_array()
{
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < MALLOC_TEST_COUNT; i++)
    {
        MemoryManager::GCptr<SmallTest> t1 = MemoryManager::manager.allocate<SmallTest>(400);
        MemoryManager::GCptr<SmallTest> t2 = MemoryManager::manager.allocate<SmallTest>(400);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Custom allocator array time: " << duration.count() << " microseconds" << std::endl;
}

void test_normal_malloc()
{
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < MALLOC_TEST_COUNT; i++)
    {
        SmallTest *t1 = new SmallTest();
        SmallTest *t2 = new SmallTest();
        SmallTest *t3 = new SmallTest();

        delete t1;
        delete t2;
        delete t3;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Malloc time for object: " << duration.count() << " microseconds" << std::endl;
}

void test_normal_malloc_array()
{
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < MALLOC_TEST_COUNT; i++)
    {
        SmallTest *t1 = new SmallTest[400];
        SmallTest *t2 = new SmallTest[400];

        delete[] t1;
        delete[] t2;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Malloc time for object array: " << duration.count() << " microseconds" << std::endl;
}



bool test_malloc()
{
    std::cout << "----------Running malloc tests-------------" << std::endl;
    test_normal_malloc();
    test_custom_allocator();
    test_normal_malloc_array();
    test_custom_allocator_array();
    return true;
}