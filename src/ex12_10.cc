#include <iostream>
#include <vector>
#include "ex12_10.hh"

using std::vector;
using std::cout;
using std::endl;

void test_copy() {
    Vec<int> nums;
    nums.push_back(8);
    nums.push_back(5);
    nums.push_back(3);
    nums.push_back(2);

    Vec<int> nums2 = nums;
    for (Vec<int>::const_iterator it = nums2.begin(); it != nums2.end(); it++) {
        cout << *it << endl;
    }

    // This should never show up in the output
    nums.push_back(42);
    
    for (Vec<int>::const_iterator it = nums2.begin(); it != nums2.end(); it++) {
        cout << *it << endl;
    }
}


int main() {
    cout << "Starting." << endl;

    vector<int> fib1 = {8, 5, 3, 2};

    Vec<int> fib2(fib1.begin(), fib1.end());

    for (Vec<int>::const_iterator it = fib2.begin(); it != fib2.end(); it++) {
        cout << *it << endl;
    }

    test_copy();

    cout << "End." << endl;
    return 0;
}
