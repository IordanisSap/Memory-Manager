#include <iostream>
#include <chrono>
#include "../MemoryManager/MemoryManager.hpp"
#include "../MemoryManager/ptr.hpp"
#include "test.hpp"

using namespace std::chrono;

bool test_single(){
    MemoryManager::ptr<SmallTest> t1 = MemoryManager::Manager::getInstance().allocate<SmallTest>();
    MemoryManager::ptr<BigTest> t2 = MemoryManager::Manager::getInstance().allocate<BigTest>();
    t1->a = 3;
    t2->b[0] = 0;
    t2->b[1] = 1;

    t2->b[49] = t1->a + t2->b[0] + t2->b[1];

    MemoryManager::ptr<SmallTest> t3 = t1;

    return t1->a == 3 && t2->b[0] == 0 && t2->b[1] == 1 && t2->b[49] == 4 && t3->a == 3;

}

bool test_array(){
    MemoryManager::ptr<SmallTest> small_array = MemoryManager::Manager::getInstance().allocate<SmallTest>(15);
    MemoryManager::ptr<BigTest> big_array = MemoryManager::Manager::getInstance().allocate<BigTest>(10);

    MemoryManager::ptr<SmallTest> small0 = small_array[0];
    MemoryManager::ptr<BigTest> big0 = big_array[0];

    MemoryManager::ptr<SmallTest> small14 = small_array[14];
    MemoryManager::ptr<BigTest> big9 = big_array[9];

    small0->a = 0;
    big0->b[0] = 0;

    small14->a = 14;
    big9->b[0] = 9;

    return small0->a == 0 && big0->b[0] == 0 && small14->a == 14 && big9->b[0] == 9;
}

bool test()
{
    return test_single() && test_array();
}
