#pragma once


// 8 Bytes
class SmallTest 
{
public:
    int a = 1;

private:
    int b = 0;
};

// 200 Bytes
class BigTest
{
public:
    int b[50];
};


bool test_alloc();
bool test_out_of_bounds();
bool test();
bool test_ref();
bool test_compaction();