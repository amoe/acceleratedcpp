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
    Vec<string> target;
    target.push_back("fry");
    target.push_back("bender");
    target.push_back("leela");

    Vec<string> source;
    source.push_back("hermes");
    source.push_back("amy");
    source.push_back("farnsworth");

    using iter_t = Vec<string>::iterator;
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

void test_vector_insert_without_realloc() {
    Vec<string> target;
    target.push_back("red");
    target.push_back("orange");
    target.push_back("yellow");
    target.push_back("green");
    target.push_back("blue");

    Vec<string> source;
    source.push_back("hermes");
    source.push_back("amy");
    source.push_back("farnsworth");

    using iter_t = Vec<string>::iterator;
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


void test_string_insert() {
    string target = "Hello, world!";
    string source = "cruel ";
    
    using iter_t = string::const_iterator;
    iter_t insert_pos = target.begin();
    insert_pos += 7;
    
    target.insert(insert_pos, source.begin(), source.end());

    cout << target << endl;
}


int main() {
    cout << "Starting." << endl;

    test_vector_insert();
    test_vector_insert_without_realloc();
    // test_string_insert();
 
    cout << "End." << endl;
    return 0;
}
