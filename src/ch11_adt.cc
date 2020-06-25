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


int main() {
    cout << "Starting." << endl;

    test_iterators();




    cout << "End." << endl;
    return 0;
}
