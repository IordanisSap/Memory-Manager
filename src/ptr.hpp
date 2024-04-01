#pragma once

#include <iostream>

class ptr
{
public:
    ptr(void *ptr = nullptr) : block(ptr) {}
    void *block;
};
