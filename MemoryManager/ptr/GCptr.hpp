#pragma once

#include <iostream>
#include "../MemoryManager.hpp"
#include "../Errors.hpp"
#include "ptr.hpp"

namespace MemoryManager
{
    template <typename T>
    class GCptr
    {
    public:
        GCptr(T *ptr = nullptr, size_t offset = 0) : m_ptr(ptr)
        {
            if (ptr == nullptr) return;
            bool isBlockOffsetValid = MemoryManager::manager.is_block_offset_valid(ptr, offset * sizeof(T));
            if (!isBlockOffsetValid)
                throw_invalid_index_error(ptr, MemoryManager::manager.get_object_size(ptr), sizeof(T), offset);
            this->offset = offset;
            MemoryManager::manager.add_reference(&this->m_ptr, m_ptr.block);
        }
        GCptr(const GCptr &other) : m_ptr(other.m_ptr)
        {
            if (other.m_ptr.block == nullptr) return;
            bool isBlockOffsetValid = other.m_ptr.block == nullptr || MemoryManager::manager.is_block_offset_valid(other.m_ptr.block, other.offset * sizeof(T));
            if (!isBlockOffsetValid)
                throw_invalid_index_error(other.m_ptr.block,MemoryManager::manager.get_object_size(other.m_ptr.block), sizeof(T), other.offset);
            this->offset = other.offset;
            MemoryManager::manager.add_reference(&this->m_ptr, m_ptr.block);
        }
        ~GCptr()
        {
            if (m_ptr.block == nullptr) return;
            MemoryManager::manager.remove_reference(&this->m_ptr, m_ptr.block);
        }
        T *operator->() { return static_cast<T*>(m_ptr.block) + offset; }
        T &operator*() { return *(static_cast<T*>(m_ptr.block) + offset); }
        GCptr operator+(int i) { return GCptr(static_cast<T*>(m_ptr.block), offset + i); }
        GCptr operator-(int i) { return GCptr(static_cast<T*>(m_ptr.block), offset - i); }
        GCptr operator[](int i) { return GCptr(static_cast<T*>(m_ptr.block), offset + i); }
        GCptr<T> &operator=(const GCptr<T> &other) // Overloading assignment operator
        {
            if (this != &other) // Avoid self-assignment
            {
                if (m_ptr.block != nullptr) MemoryManager::manager.remove_reference(&this->m_ptr, m_ptr.block);
                m_ptr.block = other.m_ptr.block;
                offset = other.offset;
                MemoryManager::manager.add_reference(&this->m_ptr, m_ptr.block);
                //std::cout << "Assigning pointer to address: " << other.m_ptr.block << std::endl;
            }
            return *this; // Return reference to the current object
        }

    private:
        ptr m_ptr;
        size_t offset = 0;
    };
}
