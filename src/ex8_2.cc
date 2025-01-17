#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <numeric>
#include "ex8_2.hh"
#include "util.hh"

using std::toupper;
using std::copy;
using std::vector;
using std::cout;
using std::endl;
using std::back_inserter;

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

void demo_copy() {
    // The destination must be able to accommodate all elements of the
    // source.
    vector<string> source_vec = {"foo", "bar", "baz"};
    vector<string> destination_vec(source_vec.size());

    using iter_t = vector<string>::const_iterator;
    iter_t result = my_copy(source_vec.begin(), source_vec.end(), destination_vec.begin());

    cout << "Destination content is now:" << endl;

    print_vector(destination_vec);

    cout << "Result is end: " << (result == destination_vec.end()) << endl;

}

bool contains_f(string value) {
    return value.find("f") != string::npos;
}

void demo_remove_copy_if() {
    vector<string> source_vec = {"foo", "bar", "baz"};
    vector<string> destination_vec;

    my_remove_copy_if(
        source_vec.begin(), source_vec.end(), back_inserter(destination_vec), contains_f
    );
    print_vector(destination_vec);
}

// Sample a -> a function for using with the transform algorithm.
string uppercase(const string& input) {
    string result;
    using iter_t = string::const_iterator;

    for (iter_t it = input.begin(); it != input.end(); it++) {
        result.push_back(toupper(*it));
    }

    return result;
}

void demo_transform() {
    vector<string> source_vec = {"foo", "bar", "baz"};
    vector<string> destination_vec;

    my_transform(
        source_vec.begin(), source_vec.end(), back_inserter(destination_vec),
        uppercase
    );

    print_vector(destination_vec);
}

void demo_accumulate() {
    vector<int> source_vec = {1,2,3};
    int seed = 0;

    int result = my_accumulate(source_vec.begin(), source_vec.end(), seed);

    cout << "Result is " << result << endl;

    int seed2 = 0;
    int& seed3 = seed2;

    int result2 = my_accumulate(source_vec.begin(), source_vec.end(), seed3);

    cout << "Seed2 is " << seed2 << endl;
    cout << "Result2 is " << result2 << endl;
}

// Search finds an entire subsequence.
void demo_search() {
    vector<int> source_vec = {10,20,30,40};
    vector<int> target_vec = {20,30};

    using iter_t = vector<int>::const_iterator;

    iter_t result = my_search(
        source_vec.begin(), source_vec.end(), target_vec.begin(), target_vec.end()
    );

    if (result == source_vec.end()) {
        cout << "std::search: subsequence not found" << endl;
    } else {
        cout << "std::search: the subsequence was found, first item " << *result << endl;
    }
}

// Find the first element where pred returns true.
void demo_find_if() {
    vector<string> vec = {"bar", "foo", "baz"};

    using iter_t = vector<string>::const_iterator;

    iter_t result = my_find_if(vec.begin(), vec.end(), contains_f);

    if (result == vec.end()) {
        cout << "find_if could not find anything satisfying predicate." << endl;
    } else {
        cout << "find_if: first element satisfying pred is " << *result << endl;
    }
}

void demo_remove_copy() {
    vector<int> vec = {10, 20, 30, 40};
    vector<int> destination_vec;

    my_remove_copy(vec.begin(), vec.end(), back_inserter(destination_vec), 30);

    cout << "remove_copy:" << endl;

    print_vector_int(destination_vec);
}

// What does remove actually do?

// Remove() is a weird function because it can't modify the bounds of the
// array.  Instead you have to use the return value.
void demo_remove() {
    vector<int> vec = {10, 20, 30, 30, 20, 10, 10, 20};

    using iter_t = vector<int>::const_iterator;
    iter_t new_end = my_remove(vec.begin(), vec.end(), 30);

    // XXX: After this, can't rely on vec.end()!  Accessing past 'new_end'
    // is UB -- guaranteed to not crash the program but with unspecified content.
    cout << "remove():" << endl;

    for (iter_t it = vec.begin(); it != new_end; it++) {
        cout << *it << endl;
    }
}

void demo_partition() {
    vector<string> source_vec = {"bar", "foo", "baz"};

    using iter_t = vector<string>::const_iterator;
    iter_t boundary = my_partition(source_vec.begin(), source_vec.end(), contains_f);

    cout << "partition()" << endl;

    cout << "True elements:" << endl;

    iter_t it;

    for (it = source_vec.begin(); it != boundary; it++) {
        cout << *it << endl;
    }

    cout << "False elements:" << endl;

    for (it = boundary; it != source_vec.end(); it++) {
        cout << *it << endl;
    }
}

int main() {
    cout << "Starting." << endl;

    demo_equal();
    demo_find();
    demo_copy();
    demo_remove_copy_if();
    demo_transform();
    demo_accumulate();
    demo_search();
    demo_find_if();
    demo_remove_copy();
    demo_remove();
    demo_partition();

    cout << "End." << endl;
    return 0;
}
