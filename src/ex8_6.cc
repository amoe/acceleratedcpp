#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include "util.hh"

using std::vector;
using std::pair;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::back_inserter;
using std::back_insert_iterator;
using std::copy;

void demo_copy1() {
    map<int, string> m;

    m[42] = "foo";
    m[56] = "bar";
    m[17] = "baz";

    print_map_int_string(m);

    vector<pair<int, string>> x;

    copy(m.begin(), m.end(), back_inserter(x));

    auto foo = back_inserter(m);

    cout << "Size of x is now " << x.size() << endl;
}

void demo_copy2() {
    map<int, string> m;
    vector<pair<int, string>> x = {{42, "foo"}};

    // We can construct the iterator fine.
    back_insert_iterator<map<int, string>> it = back_inserter(m);

    // But this fails at compile time (after template expansion) because of the
    // lack of a 'push_back' member.
    //copy(x.begin(), x.end(), it);
}

int main() {
    cout << "Starting." << endl;


    cout << "End." << endl;
    return 0;
}
