#include "../MemoryManager/ptr/GCptr.hpp"
#include "../MemoryManager/MemoryManager.hpp"
#include "test.hpp"


bool test_ref_1()
{
    MemoryManager::GCptr<int> int_array = MemoryManager::manager.allocate<int>(10); //First ref
    MemoryManager::GCptr<int> int0 = int_array[0]; //Second ref
    MemoryManager::GCptr<int> int5 = int_array[5]; //Third ref

    int_array = nullptr; //First ref removed

    *int0 = 1000; //Valid

    int0 = nullptr; //Second ref removed
    
    *int5 = 5; //Valid

    int5 = int5 - 5; //Now points to first element, which is still valid because the array has not been deallocated

    return *int5 == 1000;
    
}


bool test_ref()
{
    return test_ref_1();
}
