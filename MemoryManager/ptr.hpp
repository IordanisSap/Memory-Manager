#pragma once

#include <iostream>
#include "MemoryManager.hpp"
#include "Errors.hpp"

namespace MemoryManager
{
    template <typename T>
    class ptr
    {
    public:
        ptr(T *ptr = nullptr, size_t offset = 0) : m_ptr(ptr)
        {
            bool isBlockOffsetValid = ptr == nullptr || MemoryManager::Manager::getInstance().isBlockOffsetValid(ptr, offset * sizeof(T));
            if (!isBlockOffsetValid)
                MemoryManager::throw_invalid_index_error<T>(ptr, offset);
            this->offset = offset;
            MemoryManager::Manager::getInstance().addReference(this, m_ptr);
        }
        ptr(const ptr &other) : m_ptr(other.m_ptr)
        {
            bool isBlockOffsetValid = other.m_ptr == nullptr || MemoryManager::Manager::getInstance().isBlockOffsetValid(other.m_ptr, other.offset * sizeof(T));
            if (!isBlockOffsetValid)
                MemoryManager::throw_invalid_index_error<T>(other.m_ptr, other.offset);
            this->offset = other.offset;
            MemoryManager::Manager::getInstance().addReference(this, m_ptr);
        }
        ~ptr()
        {
            if (m_ptr == nullptr)
                return;
            MemoryManager::Manager::getInstance().removeReference(this, m_ptr);
        }
        T *operator->() { return m_ptr + offset; }
        T &operator*() { return *(m_ptr + offset); }
        ptr operator+(int i) { return ptr(m_ptr, offset + i); }
        ptr operator-(int i) { return ptr(m_ptr, offset - i); }
        ptr operator[](int i) { return ptr(m_ptr, offset + i); }
        ptr<T> &operator=(const ptr<T> &other) // Overloading assignment operator
        {
            if (this != &other) // Avoid self-assignment
            {
                MemoryManager::Manager::getInstance().removeReference(this, m_ptr);
                m_ptr = other.m_ptr;
                offset = other.offset;
                MemoryManager::Manager::getInstance().addReference(this, m_ptr);
                std::cout << "Assigning pointer to address: " << other.m_ptr << std::endl;
            }
            return *this; // Return reference to the current object
        }

    private:
        T *m_ptr;
        size_t offset = 0;
    };
}
