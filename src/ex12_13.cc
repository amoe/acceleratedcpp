#include <iostream>
#include <string>
#include "ex12_13.hh"

using std::string;
using std::cout;
using std::endl;

// Provide an assign function that could be used to assign the values in an
// array to a Vec.

int main() {
    cout << "Starting." << endl;

    Vec<int> foo;
    foo.push_back(8);
    foo.push_back(5);
    foo.push_back(3);
    foo.push_back(2);

    using iter_t = Vec<int>::const_iterator;
    for (iter_t it = foo.begin(); it != foo.end(); it++) {
        cout << *it << endl;
    }

    int some_array[] = {34, 21, 13};
    int some_array_length = sizeof(some_array) / sizeof(*some_array);

    foo.assign(some_array, some_array + some_array_length);

    for (iter_t it = foo.begin(); it != foo.end(); it++) {
        cout << *it << endl;
    }
    

    cout << "End." << endl;
    return 0;
}



