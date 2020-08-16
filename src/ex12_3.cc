#include <iostream>
#include "ex12_3.hh"

using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    StrV fut1 = "fry";
    StrV fut2 = "leela";

    cout << ((fut1 == fut2) ? "true" : "false") << endl;

    StrV fut3 = "fry";
    StrV fut4 = "fry";

    cout << ((fut3 == fut4) ? "true" : "false") << endl;

    cout << ((fut1 != fut2) ? "true" : "false") << endl;


    cout << "End." << endl;
    return 0;
}
