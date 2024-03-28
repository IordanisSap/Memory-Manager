#pragma once
#include <stdlib.h> //size_t, malloc, free
#include <new>      // bad_alloc, bad_array_new_length
#include <memory>


template <class T>
class CustomAllocator
{
public:
    typedef T value_type;
    CustomAllocator() noexcept {} // default ctor not required by C++ Standard Library

    // A converting copy constructor:
    template <class U>
    CustomAllocator(const CustomAllocator<U> &) noexcept {}
    template <class U>
    bool operator==(const CustomAllocator<U> &) const noexcept
    {
        return true;
    }
    template <class U>
    bool operator!=(const CustomAllocator<U> &) const noexcept
    {
        return false;
    }
    T *allocate(const size_t n) const;
    void deallocate(T *const p, size_t) const noexcept;
};

