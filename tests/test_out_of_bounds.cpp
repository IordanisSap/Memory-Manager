#include "GCptr.hpp"
#include "MemoryManager.hpp"
#include <chrono>
#include <iostream>
#include "test.hpp"

using namespace std::chrono;


bool test_out_of_bounds1()
{
    MemoryManager::GCptr<int> t1 = MemoryManager::manager.allocate<int>(1);
    t1[0]; //Okay
    
    try
    {
        t1[1]; //Should fail
        return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return true;
    }
}

bool test_out_of_bounds2()
{
    MemoryManager::GCptr<int> t2 = MemoryManager::manager.allocate<int>(10);
    t2[5]; //Okay
    
    try
    {
        t2[123456]; //Should fail
        return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return true;
    }
}


bool test_out_of_bounds_general()
{
    MemoryManager::GCptr<SmallTest> t1 = MemoryManager::manager.allocate<SmallTest>(10);
    MemoryManager::GCptr<BigTest> t2 = MemoryManager::manager.allocate<BigTest>(25);

    MemoryManager::GCptr<SmallTest> t3 = t1[0];
    MemoryManager::GCptr<BigTest> t4 = t2[12];

    t3->a = 5;

    *t4->b = 10;

    t2[15]->b[0] = 10;

    t1[9]->a = 10;

    try
    {
        MemoryManager::GCptr<SmallTest> t5 = t1[10]; // Should fail
        return false;
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return true;
    }
}

bool test_out_of_bounds()
{
    std::cout << "----------Running out of bounds tests-------------" << std::endl;
    return test_out_of_bounds1() && test_out_of_bounds2() && test_out_of_bounds_general();
}
