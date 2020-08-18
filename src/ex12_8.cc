#include <iostream>
#include "ex12_8.hh"

using std::cin;
using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    StrV target;

    target.getline(cin);
    
    cout << "Read: '" << target << "'" << endl;

    cout << "End." << endl;
    return 0;
}
