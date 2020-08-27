#include <iostream>
#include "ex12_10.hh"

using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    Vec<int> fib;
    fib.push_back(8);
    fib.push_back(5);
    fib.push_back(3);
    fib.push_back(2);

    for (Vec<int>::const_iterator it = fib.begin(); it != fib.end(); it++) {
        cout << *it << endl;
    }

    cout << "End." << endl;
    return 0;
}
