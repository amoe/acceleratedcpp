#include <iostream>
#include <list>
#include "ex12_1.hh"

using std::cout;
using std::endl;
using std::list;

int main() {
    cout << "Starting." << endl;
    
    StrV foo("hello world");
    cout << foo << endl;

    StrV empty;
    cout << "Empty string: '" << empty << "'" << endl;

    StrV filled_string(7, 'z');

    cout << "Filled string: '" << filled_string << "'" << endl;


    list<char> source = {'h', 'e', 'l', 'l', 'o'};
    StrV copied_string(source.begin(), source.end());


    cout << "Copied from container: '" << copied_string << "'" << endl;

    cout << "End." << endl;
    return 0;
}
