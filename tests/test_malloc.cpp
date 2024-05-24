#include <chrono>
#include "test.hpp"
#include "MemoryManager.hpp"
#include "GCptr.hpp"
#include "config.hpp"

using namespace std::chrono;

#define ALLOC_TEST_COUNT 32 * 8 * 2 * 4

MemoryManager::GCptr<SmallTest> GCptr_refs[BLOCK_NUM];
SmallTest *refs[BLOCK_NUM];

void test_custom_allocator()
{
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < ALLOC_TEST_COUNT; i++)
    {
        for (size_t j = 0; j < BLOCK_NUM; j++)
        {
            GCptr_refs[j] = MemoryManager::manager.allocate<SmallTest>();
        }
        for (size_t j = 0; j < BLOCK_NUM; j++)
        {
            GCptr_refs[j] = nullptr;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Custom allocator time: " << duration.count() << " microseconds" << std::endl;
}

void test_normal_alloc()
{
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < ALLOC_TEST_COUNT; i++)
    {
        for (size_t j = 0; j < BLOCK_NUM; j++)
        {
            refs[j] = new SmallTest();
        }
        for (size_t j = 0; j < BLOCK_NUM; j++)
        {
            delete refs[j];
            refs[j] = nullptr;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "alloc time for object: " << duration.count() << " microseconds" << std::endl;
}

bool test_alloc()
{
    std::cout << "----------Running alloc tests-------------" << std::endl;
    test_normal_alloc();
    test_custom_allocator();
    return true;
}