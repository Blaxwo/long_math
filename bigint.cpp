#include "bigint.h"
#include <fstream>
#include <cmath>
using namespace std;

bigint::bigint(): useNewMethod(false) {
    for (int i = 0; i < size; i++) {
        numbers[i] = 0;
    }}
bigint::bigint(long long number) {
    for (int i = 0; i < size; i++) {
        numbers[i] = 0;
    }
    int next = 0;
    while (number) {
        numbers[next++] = number % base;
        number /= base;
    }
}
bigint::bigint(const bigint &another) {
    for (int i = 0; i < size; i++) {
        numbers[i] = another.numbers[i];
    }
}
bigint& bigint::operator=(const bigint& other) {
    for (int i = 0; i < size; i++) {
        numbers[i] = other.numbers[i];
    }
    return *this;
}
bigint &bigint::operator=(const long long &other) {
    numbers[0] = other;
    for (int i = 1; i < size; i++) {
        numbers[i] = 0;
    }
    return *this;
}

long long& bigint::operator[](int index) {
    if (index < 0 || index >= size) {
        return numbers[0];
    }
    return numbers[index];
}
const bigint bigint::operator+(const bigint& operand) {
    for (int i = 0; i < size; i++) {
        numbers[i] += operand.numbers[i];//(*this)numbers[i]
    }

    for (int i = 0; i < size - 1; i++) {
        if (numbers[i] >= base) {
            numbers[i] -= base;
            numbers[i + 1]++;
        }
    }
    return *this;
}
const bigint bigint::operator-(const bigint &operand) {
    for (int i = 0; i < size; i++) {
        numbers[i] -= operand.numbers[i];
    }
    for (int i = 0; i < size - 1; i++) {
        if (numbers[i] < 0) {
            numbers[i] += base;
            numbers[i + 1]--;
        }
    }
    return *this;
}
const bigint bigint::operator*(const bigint &operand){
    bigint result;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            if(result.numbers[i+j]<=9'223'372'036'854'775'807){
                result.numbers[i + j] += numbers[i] * operand.numbers[j];
            }
            else{
                return -1;
            }
        }
    }

    for (int i = 0; i < size - 1; i++) {
        result.numbers[i + 1] += result.numbers[i] / base;
        result.numbers[i] %= base;
    }

    return result;
}

const bigint bigint::operator/(long long operand){
    if(operand==0){
        cout<<"You can't / 0"<<endl;
        return 1;
    }
    else{
        for (int i = size - 1; i >= 0; i--) {
            if (i) {
                numbers[i - 1] += (numbers[i] % operand) * base;
            }

            numbers[i] /= operand;
        }
        return *this;
    }
}

ostream& operator<<(ostream& out, const bigint& num) {
    string result;

    char buffer[10];

    for (int i = bigint::size - 1; i >= 0; i--) {
        sprintf(buffer, "%09d", num.numbers[i]);
        result += buffer;
    }

    int first_idx = result.find_first_not_of('0');
    if (first_idx == string::npos) {
        out << "0";
    } else {
        out << result.substr(first_idx);
    }

    return out;
}
ofstream& operator<<(ofstream& fileOut, const bigint& num) {
    string result;
    char buffer[10];

    for (int i = bigint::size - 1; i >= 0; i--) {
        sprintf(buffer, "%09d", num.numbers[i]);
        result += buffer;
    }

    int first_idx = result.find_first_not_of('0');
    if (first_idx == string::npos) {
        result= "0";
    } else {
        result=result.substr(first_idx);
    }
    fileOut.write(result.c_str(), result.size());
    return fileOut;
}
istream& operator>>(istream& in, bigint& value) {
    string input;
    in >> input;

    bigint result;
    int start = 0;
    int indexToStart;
    if(value.useNewMethod){
        indexToStart = result.size / 2;
    }
    else{
        indexToStart = result.size;
    }

    for (int i = input.length() - 1; i >= start; i -= 9) {
        int number = 0;
        int decimal = 1;
        for (int j = 0; j < 9 && i - j >= start; j++) {
            number += (input[i - j] - '0') * decimal;
            decimal *= 10;
        }
        result.numbers[indexToStart - (i - start) / 9 - 1] = number;
    }

    value = result;
    return in;
}
ifstream& operator>>(ifstream& fileIn, bigint& value) {
    string input;
    fileIn >> input;

    bigint result;

    int start = 0;
    int digits = 0;
    long long number = 0;

    for (int i = input.length() - 1; i >= start; i--) {
        char digitChar = input[i];

        if (isdigit(digitChar)) {
            int digit = digitChar - '0';
            number += digit * pow(10, digits);
            digits++;

            if (digits == 9 || i == start) {
                result.numbers[result.size - (i - start) / 9 - 1] = number;
                digits = 0;
                number = 0;
            }
        }
    }

    value = result;
    return fileIn;
}
