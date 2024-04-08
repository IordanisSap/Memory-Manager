#include "GCptr.hpp"
#include "MemoryManager.hpp"
#include "test.hpp"
#include "config.hpp"

bool test_ref_1()
{
    MemoryManager::GCptr<int> int_array = MemoryManager::manager.allocate<int>(10); // First ref
    MemoryManager::GCptr<int> int0 = int_array[0];                                  // Second ref
    MemoryManager::GCptr<int> int5 = int_array[5];                                  // Third ref

    int_array = nullptr; // First ref removed

    *int0 = 1000; // Valid

    int0 = nullptr; // Second ref removed

    *int5 = 5; // Valid

    int5 = int5 - 5; // Now points to first element, which is still valid because the array has not been deallocated

    return *int5 == 1000;
}

bool test_ref_2()
{

    if (!DEBUG) // This test is only valid in debug mode
        return true;

    MemoryManager::GCptr<int> int_single = MemoryManager::manager.allocate<int>();
    void *untracked_ref = int_single.operator->();

    *int_single = 5;
    bool is5 = *static_cast<int *>(untracked_ref) == 5;
    int_single = nullptr;
    bool is0 = *static_cast<int *>(untracked_ref) == 0; // Block should be nullified after deallocation
    return is5 && is0;
}

bool test_ref()
{
    std::cout << "----------Running reference tests----------" << std::endl;
    return test_ref_1() && test_ref_2();
}
