#include "tests/test.hpp"
#include <cassert>
#include "ConfigParser.hpp"
#include "MemoryManager/MemoryManager.hpp"

int main()
{
    MemoryManager::manager.parse_config("config.txt");
    assert(test_out_of_bounds());
    assert(test_ref());
    assert(test());
    assert(test_malloc());
    assert(test_compaction());
    return 0;
}
