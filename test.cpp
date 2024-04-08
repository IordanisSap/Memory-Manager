#include "tests/test.hpp"
#include <cassert>
#include "MemoryManager.hpp"

int main()
{
    assert(test_out_of_bounds());
    assert(test_ref());
    assert(test());
    assert(test_alloc());
    assert(test_compaction());
    return 0;
}
