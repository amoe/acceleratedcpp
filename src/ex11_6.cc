#include <iostream>
#include <string>
#include "ex11_6.hh"

using std::string;
using std::cout;
using std::endl;

void test_erase() {
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

    test_push();
    
    cout << "End." << endl;
    return 0;
}
