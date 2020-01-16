#include <iostream>
#include <vector>
#include "ex8_2.hh"

using std::vector;
using std::cout;
using std::endl;

void demo_equal() {
    // Call our implementation of std::equal.
    int myints[] = {20, 40, 60, 80, 100};
    for (int i = 0; i < 5; i++) {
        cout << myints[i] << endl;
    }

    // What does this do?  The pointer transparently works as a random access
    // iterator.  This therefore calls constructor 5 of std::vector, essentially
    // copying the array into a vector.
    vector<int> myvector(myints, myints + 5);
    using iter_t = vector<int>::const_iterator;

    for (iter_t it = myvector.begin(); it != myvector.end(); it++) {
        cout << *it << endl;
    }

    bool result = my_equal(myvector.begin(), myvector.end(), myints);
    cout << "Result was " << result << endl;

    myints[3] = 81;

    bool result2 = my_equal(myvector.begin(), myvector.end(), myints);
    cout << "Result was " << result2 << endl;

}

void demo_find() {
    vector<int> myvector = {10, 20, 30, 40};
    using iter_t = vector<int>::const_iterator;

    iter_t it1;
    it1 = my_find(myvector.begin(), myvector.end(), 30);
    cout << "Value found: " << *it1 << endl;


    iter_t it2;
    it2 = my_find(myvector.begin(), myvector.end(), 50);
    if (it2 == myvector.end()) {
        cout << "Value 50 not found, as expected." << endl;
    } else {
        cout << "DANGER: Something weird happened." << endl;
    }
}

int main() {
    cout << "Starting." << endl;

    demo_equal();
    demo_find();

//find(b, e, t)

    cout << "End." << endl;
    return 0;
}
