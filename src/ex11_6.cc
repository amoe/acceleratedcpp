#include <iostream>
#include <string>
#include "ex11_6.hh"

using std::string;
using std::cout;
using std::endl;

void test_erase() {
    cout << "Testing erase()" << endl;

    Vec<int> fib;
    fib.push_back(8);
    fib.push_back(5);
    fib.push_back(3);
    fib.push_back(2);


    for (Vec<int>::const_iterator it = fib.begin(); it != fib.end(); it++) {
        cout << *it << endl;
    }

    Vec<int>::iterator it = fib.begin();
    it++;
    fib.erase(it);

    for (Vec<int>::const_iterator it = fib.begin(); it != fib.end(); it++) {
        cout << *it << endl;
    }

    cout << "fib.size() = " << fib.size() << endl;

    cout << "Finished testing erase()" << endl;
}


void test_clear() {
    Vec<int> fib;
    fib.push_back(8);
    fib.push_back(5);
    fib.push_back(3);
    fib.push_back(2);


    for (Vec<int>::const_iterator it = fib.begin(); it != fib.end(); it++) {
        cout << *it << endl;
    }


    fib.clear();

    cout << "Iterating..." << endl;
    for (Vec<int>::const_iterator it = fib.begin(); it != fib.end(); it++) {
        cout << *it << endl;
    }
    cout << "Iteration end." << endl;


    cout << "fib.size() = " << fib.size() << endl;
}

int main() {
    cout << "Starting." << endl;

    test_erase();
    test_clear();
    
    cout << "End." << endl;
    return 0;
}
