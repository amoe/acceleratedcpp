#include <iostream>
#include "ex12_7.hh"

using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    StrV s1("hello world");

    // Rule of three stuff for the iterators
    StrV::iterator it1;

    it1 = s1.begin();
    StrV::iterator it2(it1);
    it2 = it1;
    it2++;

    cout << "Test compare: "
         << (it1 == it2 ? "true" : "false")
         << endl;

    cout << "Dereference: '" << *it1 << "'" << endl;


    *it1 = 'y';
    cout << "Deref/assign: '" << *it1 << "'" << endl;

    it1++;
    cout << "Increment: '" << *it1 << "'" << endl;


    it1--;
    cout << "Decrement: '" << *it1 << "'" << endl;

    cout << "Add: '" << *(it1 + 2) << "'" << endl;
    cout << "Subtract: '" << *((it1 + 2) - 1) << "'" << endl;


    cout << "Compare: " << ((it2 > it1) ? "greater" : "lesser") << endl;


    it1 += 1;
    cout << "Compound assign: '" << *it1 << "'" << endl;
    it1 -= 1;

    cout << "Offset dereference: '" << it1[4] << "'" << endl;

    cout << "End." << endl;
    return 0;
}
