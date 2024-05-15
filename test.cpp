#include "tests/test.hpp"
#include <cassert>
#include "MemoryManager.hpp"
#include "config.hpp"

int main()
{
    //assert(test_out_of_bounds());
    //assert(test_ref());
    //assert(test());
    assert(test_alloc());
#if ENABLE_EXPERIMENTAL_COMPACTION == 1
    assert(test_compaction());
#endif
    return 0;
}
