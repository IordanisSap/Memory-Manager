#include <chrono>
#include "test.hpp"
#include "MemoryManager.hpp"
#include "GCptr.hpp"
#include "config.hpp"

using namespace std::chrono;

#define ALLOC_TEST_COUNT 1

void test_custom_allocator()
{
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < ALLOC_TEST_COUNT; i++)
    {
        MemoryManager::GCptr<SmallTest> refs[BLOCK_NUM];
        for (size_t j = 0; j < BLOCK_NUM; j++)
        {
            refs[j] = MemoryManager::manager.allocate<SmallTest>();
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Custom allocator time: " << duration.count() << " microseconds" << std::endl;
}

void test_custom_allocator_array()
{
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < ALLOC_TEST_COUNT; i++)
    {
        MemoryManager::GCptr<SmallTest> t1 = MemoryManager::manager.allocate<SmallTest>(390);
        MemoryManager::GCptr<SmallTest> t2 = MemoryManager::manager.allocate<SmallTest>(390);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Custom allocator array time: " << duration.count() << " microseconds" << std::endl;
}

void test_normal_alloc()
{
    auto start = high_resolution_clock::now();
    SmallTest *refs[BLOCK_NUM];
    for (size_t i = 0; i < ALLOC_TEST_COUNT; i++)
    {
        for (size_t j = 0; j < BLOCK_NUM; j++)
        {
            refs[j] = new SmallTest();
        }
        for (size_t j = 0; j < BLOCK_NUM; j++)
        {
            delete refs[j];
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "alloc time for object: " << duration.count() << " microseconds" << std::endl;
}

void test_normal_alloc_array()
{
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < ALLOC_TEST_COUNT; i++)
    {
        SmallTest *t1 = new SmallTest[400];
        SmallTest *t2 = new SmallTest[400];

        delete[] t1;
        delete[] t2;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "alloc time for object array: " << duration.count() << " microseconds" << std::endl;
}

bool test_alloc()
{
    std::cout << "----------Running alloc tests-------------" << std::endl;
    test_normal_alloc();
    test_custom_allocator();
    test_normal_alloc_array();
    test_custom_allocator_array();
    return true;
}