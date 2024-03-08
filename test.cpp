#include "MemoryManager.hpp"
#include <iostream>

int main()
{
    void *test = MemoryManager::getInstance().allocate(512*1 - 4);
    void *test2 = MemoryManager::getInstance().allocate(512*1 - 4);
    void *test3 = MemoryManager::getInstance().allocate(512*1 - 4);

    static_cast<int *>(test)[0] = 1;
    MemoryManager::getInstance().deallocate(test);
    void *test4 = MemoryManager::getInstance().allocate(512*1 - 4);

    return 0;
}
