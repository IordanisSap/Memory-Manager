#include <iostream>
#include <chrono>
#include "../MemoryManager/MemoryManager.hpp"
#include "../MemoryManager/ptr/GCptr.hpp"
#include "test.hpp"

using namespace std::chrono;

bool test_single(){
    MemoryManager::GCptr<SmallTest> t1 = MemoryManager::manager.allocate<SmallTest>();
    MemoryManager::GCptr<BigTest> t2 = MemoryManager::manager.allocate<BigTest>();
    t1->a = 3;
    t2->b[0] = 0;
    t2->b[1] = 1;

    t2->b[49] = t1->a + t2->b[0] + t2->b[1];

    MemoryManager::GCptr<SmallTest> t3 = t1;

    return t1->a == 3 && t2->b[0] == 0 && t2->b[1] == 1 && t2->b[49] == 4 && t3->a == 3;

}

bool test_array(){
    MemoryManager::GCptr<SmallTest> small_array = MemoryManager::manager.allocate<SmallTest>(15);
    MemoryManager::GCptr<BigTest> big_array = MemoryManager::manager.allocate<BigTest>(10);

    MemoryManager::GCptr<SmallTest> small0 = small_array[0];
    MemoryManager::GCptr<BigTest> big0 = big_array[0];

    MemoryManager::GCptr<SmallTest> small14 = small_array[14];
    MemoryManager::GCptr<BigTest> big9 = big_array[9];

    small0->a = 0;
    big0->b[0] = 0;

    small14->a = 14;
    big9->b[0] = 9;

    return small0->a == 0 && big0->b[0] == 0 && small14->a == 14 && big9->b[0] == 9;
}

bool test()
{
    std::cout << "----------Running general tests----------" << std::endl;
    return test_single() && test_array();
}
