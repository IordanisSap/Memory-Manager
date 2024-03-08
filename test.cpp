#include <iostream>
#include <chrono>
#include "MemoryManager.hpp"

using namespace std::chrono;


class SmallTest
{
public:
    SmallTest() {  }
    ~SmallTest() { }
private:
    int b[20];
};


class BigTest
{
public:
    BigTest() { }
    ~BigTest() {  }
private:
    int b[300];
};


int main()
{
    auto start = high_resolution_clock::now();
    void* test1;
    void* test2;
    for (int i = 0; i < 50000; ++i)
    {
        SmallTest *test1 = new SmallTest();
        BigTest *test2 = new BigTest();
        delete test1;
        delete test2;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by test: "
              << duration.count() << " microseconds" << std::endl;
    return 0;
}
