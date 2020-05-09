#include <iostream>
#include <algorithm>
#include <vector>
#include "ex8_7.hh"

using std::vector;
using std::cout;
using std::endl;
using std::max;

double foo() {
    return 42;
}

int main() {
    cout << "Starting." << endl;



    int ival1 = 41;
    int ival2 = 43;

    int result1 = my_max(ival1, ival2);

    cout << "The maximum of ints is " << result1 << endl;


    double dval1 = 41.0;
    double dval2 = 43.0;

    double result2 = my_max(dval1, dval2);

    cout << "The maximum of doubles is " << result2 << endl;

    // This works, but it's basically a fluke of the compiler doing
    // IMPLICIT CONVERSIONS when you return a value of the wrong type.
    int result3 = my_max2(dval1, ival2);
    cout << "The maximum of doubles (using max2) is " << result3 << endl;


    // But demonstrate that it's wrong, we can use this example, as the
    // attempt to return an iterator for vector<double> from a function
    // declared to return an iterator for vector<int> can never be implicitly
    // converted and as such will cause a compiler error.
    vector<int> foo = {1,2,3};
    vector<double> bar = {4.0,5.0,6.0};

    using iter1_t = vector<int>::const_iterator;
    using iter2_t = vector<double>::const_iterator;

    iter1_t i1 = foo.begin();
    iter2_t i2 = bar.begin();

// error: could not convert 'b' from '__normal_iterator<const double*,vector<double>>' to '__normal_iterator<const int*,vector<int>>'
//    auto result = my_max2(i1, i2);


    cout << "End." << endl;
    return 0;
}
