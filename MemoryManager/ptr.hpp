#ifndef PTR_HPP
#define PTR_HPP

#include <iostream>
#include "MemoryManager.hpp"
#include "Errors.hpp"

namespace MemoryManager
{
    template <typename T>
    class ptr
    {
    public:
        ptr(T *ptr = nullptr,size_t offset=0) : m_ptr(ptr)
        {
            bool isBlockOffsetValid = MemoryManager::Manager::getInstance().isBlockOffsetValid(ptr, offset * sizeof(T));
            if (!isBlockOffsetValid) MemoryManager::throw_invalid_index_error<T>(ptr, offset);
            this->offset = offset;
            std::cout << "Creating pointer to address: " << m_ptr << std::endl;
            MemoryManager::Manager::getInstance().addReference(this, m_ptr);
        }
        ~ptr()
        {
            if (m_ptr == nullptr)
                return;
            MemoryManager::Manager::getInstance().removeReference(this, m_ptr);
            std::cout << "Deleting pointer to address: " << m_ptr << std::endl;
        }
        T *operator->() { return m_ptr + offset; }
        T &operator*() { return *(m_ptr + offset); }
        ptr operator+(int i) { return ptr(m_ptr, offset + i);  }
        ptr operator-(int i) { return ptr(m_ptr, offset - i);  }
        ptr operator[](int i) { return ptr(m_ptr, offset + i); }
        ptr<T> &operator=(const ptr<T> &other) // Overloading assignment operator
        {
            if (this != &other) // Avoid self-assignment
            {
                MemoryManager::Manager::getInstance().removeReference(this, m_ptr);
                m_ptr = other.m_ptr;
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

#endif