#include <iostream>
#include <chrono>
#include "MemoryManager/MemoryManager.hpp"

using namespace std::chrono;


class SmallTest
{
public:
    SmallTest() {  }
    ~SmallTest() { }
private:
    int b[15];
};


class BigTest
{
public:
    BigTest() { }
    ~BigTest() {  }
private:
    int b[25];
};


int main()
{
    auto start = high_resolution_clock::now();
    SmallTest **test1 = new SmallTest*[5];
    BigTest **test2 = new BigTest*[5];
    for (int i = 0; i < 5; ++i)
    {
        test1[i] = new SmallTest();
        test2[i] = new BigTest();
    }
    for (int i = 0; i < 5; ++i)
    {
        delete test1[i];
        delete test2[i];
    }

    delete[] test1;
    delete[] test2;
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by test: "
              << duration.count() << " microseconds" << std::endl;
    return 0;
}
