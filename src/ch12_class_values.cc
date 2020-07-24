#include <iostream>
#include <cstring>
#include <iterator>
#include "vec.hh"

using std::cout;
using std::endl;
using std::copy;
using std::strlen;
using std::back_inserter;

class Str {
public:
    using size_type = Vec<char>::size_type;

    Str() { }

    Str(size_type n, char c): data(n, c) { }

    Str(const char* cp) {
        copy(cp, cp + strlen(cp), back_inserter(data));
    }

    void print() {
        for (Vec<char>::const_iterator it = data.begin(); it != data.end(); it++) {
            cout << *it;
        }
        cout << endl;
    }

private:
    Vec<char> data;
};

int main() {
    cout << "Starting." << endl;

    Str s1;   // Blank string
    Str s2("hello world");    // Char* constructor
    Str s3(8, 'f');

    cout << "s1: ";
    s1.print();

    cout << "s2: ";
    s2.print();

    cout << "s3: ";
    s3.print();


    cout << "End." << endl;
    return 0;
}
