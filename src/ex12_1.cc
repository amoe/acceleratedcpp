#include <iostream>
#include "ex12_1.hh"

using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;
    
    StrV foo("hello world");
    cout << foo << endl;

    StrV empty;
    cout << "Empty string: '" << empty << "'" << endl;

    StrV filled_string(7, 'z');

    cout << "Filled string: '" << filled_string << endl;



    cout << "End." << endl;
    return 0;
}
