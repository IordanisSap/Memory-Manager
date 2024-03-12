#include "../MemoryManager/ptr.hpp"
#include "../MemoryManager/MemoryManager.hpp"
#include <chrono>
#include "test.hpp"

using namespace std::chrono;


bool test_malloc()
{
    MemoryManager::ptr<SmallTest> t1 = MemoryManager::Manager::getInstance().allocate<SmallTest>();
    MemoryManager::ptr<BigTest> t2 = MemoryManager::Manager::getInstance().allocate<BigTest>();
    // MemoryManager::ptr<SmallTest> t3 = MemoryManager::Manager::getInstance().allocate<SmallTest>();

    t2 = MemoryManager::Manager::getInstance().allocate<BigTest>();
    t2 = nullptr;
    t1 = MemoryManager::Manager::getInstance().allocate<SmallTest>();
    t1 = nullptr;

    return true;
}
