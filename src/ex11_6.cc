#include <iostream>
#include <string>
#include "ex11_6.hh"

using std::string;
using std::cout;
using std::endl;

void test_iterators() {
    Vec<string> stuff;
    const Vec<string>& stuff_alias = stuff;

    Vec<string>::iterator iter1;

    using sz1 = Vec<string>::size_type;
    sz1 baz;

    auto& foo = stuff_alias[0];
    auto& bar = stuff[0];
}

void test_push() {
   Vec<int> fib;
   fib.push_back(8);
    fib.push_back(5);
    fib.push_back(3);
    fib.push_back(2);


    for (Vec<int>::const_iterator it = fib.begin(); it != fib.end(); it++) {
        cout << *it << endl;
    }
}

void test_fill() {
    Vec<int> v(10, 42);
  
    for (Vec<int>::const_iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
}

void test_assignment() {
    Vec<int> nums;
    nums.push_back(8);
    nums.push_back(5);
    nums.push_back(3);
    nums.push_back(2);

    Vec<int> nums2 = nums;
    for (Vec<int>::const_iterator it = nums2.begin(); it != nums2.end(); it++) {
        cout << *it << endl;
    }

    nums.push_back(42);
    
    for (Vec<int>::const_iterator it = nums2.begin(); it != nums2.end(); it++) {
        cout << *it << endl;
    }
}


int main() {
    cout << "Starting." << endl;

    test_iterators();
    test_push();
    test_fill();
    test_assignment();
    
    cout << "End." << endl;
    return 0;
}
