#ifndef PTR_HPP
#define PTR_HPP

#include <iostream>
#include "MemoryManager.hpp"

namespace MemoryManager
{
    template <typename T>
    class ptr
    {
    public:
        ptr(T *ptr = nullptr) : m_ptr(ptr)
        {
            MemoryManager::Manager::getInstance().addReference(this, m_ptr);
            std::cout << "Creating pointer to address: " << m_ptr << std::endl;
        }
        ~ptr()
        {
            if (m_ptr == nullptr) return;
            MemoryManager::Manager::getInstance().removeReference(this, m_ptr);
            std::cout << "Deleting pointer to address: " << m_ptr << std::endl;
        }
        T *operator->() { return m_ptr; }
        T &operator*() { return *m_ptr; }
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
    };
}

#endif