#include <iostream>
#include <chrono>

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
    SmallTest **test1 = new SmallTest*[4];
    BigTest **test2 = new BigTest*[4];
    for (int i = 0; i < 4; ++i)
    {
        test1[i] = new SmallTest();
        test2[i] = new BigTest();
    }
    for (int i = 0; i < 4; ++i)
    {
        delete test1[i];
        delete test2[i];
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by test: "
              << duration.count() << " microseconds" << std::endl;
    return 0;
}
