#include <iostream>
#include <chrono>
#include "MemoryManager/MemoryManager.hpp"
#include "MemoryManager/ptr.hpp"

using namespace std::chrono;

class SmallTest
{
public:
    SmallTest() {}
    ~SmallTest() {}
    int y=1;

private:
    int k = 0;
    int b[25];
};

class BigTest
{
public:
    BigTest() {}
    ~BigTest() {}

private:
    int b[150];
};

void test(){
    MemoryManager::ptr<SmallTest> t1 = MemoryManager::Manager::getInstance().allocate<SmallTest>();
    MemoryManager::ptr<BigTest> t2 = MemoryManager::Manager::getInstance().allocate<BigTest>();
    MemoryManager::ptr<SmallTest> t3 = MemoryManager::Manager::getInstance().allocate<SmallTest>();


    t2 = MemoryManager::Manager::getInstance().allocate<BigTest>();
    t2 = nullptr;
    t1 = nullptr;
    // t1->y=5;
    // std::cout << "t1: " << t1->y << std::endl; 
}

int main()
{
    test();
    // test();


    // auto start = high_resolution_clock::now();
    // SmallTest **test1 = MemoryManager::Manager::getInstance().allocate<SmallTest *>(5);
    // BigTest **test2 = MemoryManager::Manager::getInstance().allocate<BigTest *>(5);
    // for (int i = 0; i < 5; ++i)
    // {
    //     test1[i] = MemoryManager::Manager::getInstance().allocate<SmallTest>();
    //     test2[i] = MemoryManager::Manager::getInstance().allocate<BigTest>();
    // }
    // for (int i = 0; i < 5; ++i)
    // {
    //     MemoryManager::Manager::getInstance().deallocate(test1[i]);
    //     MemoryManager::Manager::getInstance().deallocate(test2[i]);
    // }

    // MemoryManager::Manager::getInstance().deallocate(test1);
    // MemoryManager::Manager::getInstance().deallocate(test2);

    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // std::cout << "Time taken by test: "
    //           << duration.count() << " microseconds" << std::endl;
    return 0;
}
