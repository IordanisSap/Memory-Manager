#include "tests/test.hpp"
#include <cassert>

int main()
{
    assert(test_out_of_bounds());
    assert(test_ref());
    assert(test_malloc());
    assert(test());
    return 0;
}
