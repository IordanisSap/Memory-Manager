#include "../MemoryManager.hpp"
#include "CustomAllocator.hpp"


template <class T>
T *CustomAllocator<T>::allocate(const size_t n) const
{
    if (n == 0)
    {
        return nullptr;
    }
    if (n > static_cast<size_t>(-1) / sizeof(T))
    {
        throw std::bad_array_new_length();
    }
    void *const pv = MemoryManager::manager.allocate<T>(n);
    if (!pv)
    {
        throw std::bad_alloc();
    }
    return static_cast<T *>(pv);
}

template <class T>
void CustomAllocator<T>::deallocate(T *const p, size_t) const noexcept
{
    MemoryManager::manager.deallocate(p);
}