#pragma once
using namespace std;
#include <iostream>
struct bigint{
    bool useNewMethod;
    static const long long base = 1e9;
    static const int size = 10;
    long long numbers[size];
    bigint();
    bigint(const bigint& another);
    bigint(long long number);

    const bigint operator+(const bigint& operand);
    const bigint operator-(const bigint& operand);
    const bigint operator/(long long operand);
    const bigint operator*(const bigint& operand);

    bigint& operator=(const bigint& value);
    virtual bigint& operator=(const long long& value);
    long long& operator[](int index);

    friend ostream& operator<<(ostream& os, const bigint& value);
    friend istream& operator>>(istream& os, bigint& value);
};