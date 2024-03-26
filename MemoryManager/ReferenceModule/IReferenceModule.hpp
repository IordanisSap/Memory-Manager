#pragma once

#include <iostream>
#include "../ptr/ptr.hpp"
#include <list>

namespace MemoryManager
{
    class IReferenceModule
    {
    public:
        virtual void add_reference(ptr *ptr, void *block) = 0;
        virtual bool remove_reference(ptr *ptr, void *block) = 0;
        virtual std::list<ptr *> get_references(void *block) = 0;
    };
}


