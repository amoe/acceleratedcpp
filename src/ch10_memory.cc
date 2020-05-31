#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::back_inserter;
using std::copy;
using std::cout;
using std::endl;

int square(int x) {
    return x * x;
}

int main() {
    cout << "Starting." << endl;

    // Basic pointers
    int x = 5;
    int* p = &x;

    cout << "x = " << x << endl;

    *p = 6;
    cout << "x = " << x << endl;



    // Function pointers
    int (*fp)(int);

    fp = square;

    int result = fp(4);

    cout << "result (call-through-pointer) is " << result << endl;


    // Copy through array
    vector<double> dv;
    const int number_of_dimensions = 3;
    double coords[number_of_dimensions] = {4,5,6};
    copy(
        coords,   // Has a pointer type
        coords + 3,  // Is still usable for comparisons
        back_inserter(dv)
    );


    using iter_t = vector<double>::const_iterator;
    for (iter_t it = dv.begin(); it != dv.end(); it++) {
        cout << *it << endl;
    }

    // Construct from pointer

    vector<double> dv2(coords, coords + 3);
    using iter_t = vector<double>::const_iterator;
    for (iter_t it = dv2.begin(); it != dv2.end(); it++) {
        cout << *it << endl;
    }

    // Create array without specifying length.
    const int month_lengths[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };


    cout << "End." << endl;
    return 0;
}
