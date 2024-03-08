#include "MemoryManager.hpp"
#include <iostream>

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
    void* test1;
    void* test2;
    for (int i = 0; i < 100; ++i)
    {
        void *test1 = new SmallTest();
        void *test2 = new BigTest();
        delete test1;
        delete test2;
    }
    return 0;
}
