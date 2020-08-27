#include <iostream>
#include <iterator>
#include "ex12_9.hh"

using std::ostream_iterator;
using std::cout;
using std::endl;
using std::cin;

int main() {
    cout << "Starting." << endl;

    // StrV s1("hello world");
    // cout << "String contents: '" << s1 << "'" << endl;

    cout << "reading: ";


    StrV s2;
    cin >> s2;
    cout << "read string: '" << s2 << "'" << endl;
    
    cout << "End." << endl;
    return 0;
}
