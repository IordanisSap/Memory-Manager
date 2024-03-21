#pragma once

#include <iostream>
#include "../ptr.hpp"
#include <list>

namespace MemoryManager
{
    class IReferenceModule
    {
    public:
        virtual void addReference(ptr *ptr, void *block) = 0;
        virtual bool removeReference(ptr *ptr, void *block) = 0;
        virtual std::list<ptr *> getRefs(void *block) = 0;
    };
}


