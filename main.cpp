#include <iostream>
#include <fstream>
#include "bigint.h"

using namespace std;

class BigIntWrapper {
public:
    BigIntWrapper(bigint *obj) : obj(obj) {}

    bigint *operator->() {
        return obj;
    }

private:
    bigint *obj;
};

struct PseudoAssignment : public bigint {
public:
    int start;
    PseudoAssignment &operator()(int start, int end) {
        if (start < 0 || start >= size || end < 0 || end >= size) {
            cout << "Invalid range. Range should be between 0 and " << size - 1 << endl;
            return *this;
        }
        if (start == end) {
            numbers[start] = 0;
            return *this;
        }
        if (start > end) {
            int temp = start;
            start = end;
            end = temp;
        }
        numbers[start] = 0;
        for (int i = start + 1; i < size; ++i) {
            if (i + end - start < size) {
                numbers[i] = numbers[i + end - start];
            } else {
                numbers[i] = 0;
            }
        }
        return *this;
    }

    bigint &operator=(const long long &other) override{
        numbers[start] = other;
        return *this;
    }

    PseudoAssignment(int _start) : start(_start) {}
};


int main() {
    int choice = 0;
    do {
        cout << endl << "0) Stop" << endl;
        cout << "1) Add numbers" << endl;
        cout << "2) Subtract numbers" << endl;
        cout << "3) Multiply numbers" << endl;
        cout << "4) Divide numbers" << endl;
        cout << "5) Write number to file" << endl;
        cout << "6) Read number from file" << endl;
        cout << "7) Assign second number to first" << endl;
        cout << "8) Receive value of first bigint (using ->)" << endl;
        cout << "9) Realizing value(x,y)=n" << endl;
        cin >> choice;
        bigint first;
        bigint second;
        long long long_second;
        bigint result;
        switch (choice) {
            case 0: {
                cout << "Finishing program" << endl;
                return 0;
            }
            case 1: {
                cout << "First number:" << endl;
                cin >> first;
                cout << "Second number:" << endl;
                cin >> second;
                cout << first << "+" << second << "=" << first + second;
                break;
            }
            case 2: {
                cout << "First number:" << endl;
                cin >> first;
                cout << "Second number:" << endl;
                cin >> second;
                cout << first << "-" << second << "=" << first - second;
                break;
            }
            case 3: {
                first.useNewMethod = true;
                second.useNewMethod = true;
                cout << "First number:" << endl;
                cin >> first;
                cout << "Second number:" << endl;
                cin >> second;
                cout << first << "*" << second << "=" << first * second;
                break;
            }
            case 4: {
                cout << "First number:" << endl;
                cin >> first;
                cout << "Second number:" << endl;
                cin >> long_second;
                cout << first << "/" << long_second << "=" << first / long_second;
                break;
            }
            case 5: {
                ofstream f("C:\\Users\\38093\\Desktop\\bignumber.txt");
                if (!f) {
                    cout << "Can't open file" << endl;
                    return 1;
                } else {
                    bigint number;
                    cout << "Input number to write to file:" << endl;
                    cin >> number;
                    f << number;
                    cout << "Successfully added number to file" << endl;
                }
                f.close();
                break;
            }
            case 6: {
                ifstream f("C:\\Users\\38093\\Desktop\\bignumber.txt");
                if (!f) {
                    cout << "Can't open file" << endl;
                    return 1;
                } else {
                    bigint number;
                    cout << "Number from file:" << endl;
                    f >> number;
                    cout << number << endl;
                }
                f.close();
                break;
            }
            case 7: {
                cout << "Input first:" << endl;
                cin >> first;
                cout << "Input second:" << endl;
                cin >> second;
                first = second;
                cout << "first:" << first << endl << "second:" << second << endl;
                break;
            }
            case 8: {
                cout << "Input first:" << endl;
                cin >> first;
                BigIntWrapper wrapper1(&first);
                cout << "first:" << endl;
                int i = 0;
                for (long long num: wrapper1->numbers) {
                    cout << i++ << ": " << num << endl;
                }
                break;
            }
            case 9: {
                int x, y;
                long long n;
                cout << "Input x for value(x,y)=n" << endl;
                cin >> x;
                cout << "Input y for value(x,y)=n" << endl;
                cin >> y;
                cout << "Input n for value(x,y)=n" << endl;
                cin >> n;
                cout << "Input value:" << endl;
                PseudoAssignment value = PseudoAssignment(x);
                cin >> value;
                cout << "value:" << value << endl;
                cout << "Value of value after value(x,y)=n" << endl;
                bigint smth = value(x, y) = n;
                cout << "value:" << smth << endl;
                break;
            }
            default: {
                cout << "Incorrect choice";
                break;
            }
        }
    } while (true);
}
