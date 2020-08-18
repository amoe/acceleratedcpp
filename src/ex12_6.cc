#include <iostream>
#include "ex12_6.hh"

using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    StrV s1;

    if (s1) {
        cout << "I shan't be printed" << endl;
    } else {
        cout << "the empty string was successfully false" << endl;
    }

    StrV s2("fry");
    if (s2) {
        cout << "the non-empty string was successfully true" << endl;
    } else {
        cout << "I shan't be printed" << endl;
    }

    cout << "End." << endl;
    return 0;
}
