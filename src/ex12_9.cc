#include <iostream>
#include <iterator>
#include "ex12_9.hh"

using std::ostream_iterator;
using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    StrV s1("hello world");
    cout << "String contents: '" << s1 << "'" << endl;
    
    cout << "End." << endl;
    return 0;
}
