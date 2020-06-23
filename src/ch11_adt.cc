#include <iostream>
#include <string>
#include "ch11_adt.hh"

using std::string;
using std::cout;
using std::endl;

// Chapter 11: "Defining abstract data types"


int main() {
    cout << "Starting." << endl;

    Vec<string> stuff;
    const Vec<string>& stuff_alias = stuff;

    Vec<string>::iterator iter1;

    using sz1 = Vec<string>::size_type;

    auto& foo = stuff_alias[0];
    auto& bar = stuff[0];


    // for (sz1 i = 0; i < stuff.size(); i++) {
    //     cout << "An item" << stuff[i] << endl;
    // }


    cout << "End." << endl;
    return 0;
}
