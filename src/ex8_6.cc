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

int main() {
    cout << "Starting." << endl;

    map<int, string> m;

    m[42] = "foo";
    m[56] = "bar";
    m[17] = "baz";

    print_map_int_string(m);

    vector<pair<int, string>> x;

    copy(m.begin(), m.end(), back_inserter(x));

    cout << "Size of x is now " << x.size() << endl;

    cout << "End." << endl;
    return 0;
}
