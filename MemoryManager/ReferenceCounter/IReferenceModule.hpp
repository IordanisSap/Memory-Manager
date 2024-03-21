#pragma once

#include <iostream>
#include "../ptr.hpp"

namespace MemoryManager
{
    class IReferenceModule
    {
    public:
        virtual void addReference(ptr *ptr, void *block) = 0;
        virtual bool removeReference(ptr *ptr, void *block) = 0;
    };
}


