#include <iostream>
#include "GarbageCollector/GC_ptr/GC_ptr.hpp"


void test(){
    GC::ptr<int> p2(new int(5)); // Dynamically allocate memory for an integer and store it in the ptr
    p2 = nullptr;
}

int main() {
    // GC::ptr<int> p1(new int(5)); // Dynamically allocate memory for an integer and store it in the ptr
    //GC::ptr<int> p2(new int(6)); // Dynamically allocate memory for an integer and store it in the ptr
    // p1 = new int(7);
    test();
    return 0;
}