#pragma once


// 8 Bytes
class SmallTest 
{
public:
    SmallTest() {}
    ~SmallTest() {}
    int a = 1;

private:
    int b = 0;
};

// 200 Bytes
class BigTest
{
public:
    BigTest() {}
    ~BigTest() {}
    int b[50];
};


bool test_malloc();
bool test_out_of_bounds();
bool test();
bool test_ref();