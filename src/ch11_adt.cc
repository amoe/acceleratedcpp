#include <iostream>
#include <string>
#include "ch11_adt.hh"

using std::string;
using std::cout;
using std::endl;

// Chapter 11: "Defining abstract data types"

void test_iterators() {
    Vec<string> stuff;
    const Vec<string>& stuff_alias = stuff;

    Vec<string>::iterator iter1;

    using sz1 = Vec<string>::size_type;
    sz1 baz;

    auto& foo = stuff_alias[0];
    auto& bar = stuff[0];
}

void test_push() {
   Vec<int> fib;
   fib.push_back(8);
    fib.push_back(5);
    fib.push_back(3);
    fib.push_back(2);


    for (Vec<int>::const_iterator it = fib.begin(); it != fib.end(); it++) {
        cout << *it << endl;
    }
}


int main() {
    cout << "Starting." << endl;

    test_iterators();
    test_push();
//    test_fill();

    cout << "End." << endl;
    return 0;
}
