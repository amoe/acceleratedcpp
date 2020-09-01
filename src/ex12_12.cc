#include <iostream>
#include <vector>
#include <string>
#include "ex12_12.hh"

using std::vector;
using std::string;
using std::cout;
using std::endl;

// "Define the insert function that takes two iterators for the Vec and Str
// classes." p316

// ret.insert(ret.end(), bottom.begin(), bottom.end());

// c.insert(d, b, e)
// Copies elements denoted by iterators in the range [b, e) and inserts them into c immediately
// before d .

void test_vector_insert() {

    vector<string> target;
    target.push_back("fry");
    target.push_back("bender");
    target.push_back("leela");

    vector<string> source;
    source.push_back("hermes");
    source.push_back("amy");
    source.push_back("farnsworth");

    using iter_t = vector<string>::const_iterator;
    iter_t insert_pos = target.begin();
    insert_pos++;

    cout << "Before:" << endl;

    for (iter_t it = target.begin(); it != target.end(); it++)
        cout << *it << endl;

    target.insert(insert_pos, source.begin(), source.end());

    cout << "After:" << endl;

    for (iter_t it = target.begin(); it != target.end(); it++)
        cout << *it << endl;
}


int main() {
    cout << "Starting." << endl;

    test_vector_insert();

    cout << "End." << endl;
    return 0;
}
