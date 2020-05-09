#include <iostream>
#include <map>
#include <string>
#include "util.hh"

using std::cout;
using std::endl;
using std::map;
using std::string;

int main() {
    cout << "Starting." << endl;

    map<int, string> m;

    m[42] = "foo";
    m[56] = "bar";
    m[17] = "baz";

    print_map_int_string(m);
    
    cout << "End." << endl;
    return 0;
}
