#include <iostream>
#include "ex12_1.hh"

using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;
    
    StrV foo("hello world");
    cout << foo << endl;

    cout << "End." << endl;
    return 0;
}