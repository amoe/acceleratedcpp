#include <iostream>
#include "ex12_5.hh"

using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    // This can never work, as one parameter must be a user defined type.
    StrV result1 = "bar" + StrV("foo");
    cout << result1 << endl;

    StrV result2 = StrV("foo") + "bar";
    cout << result2 << endl;

    cout << "End." << endl;
    return 0;
}
