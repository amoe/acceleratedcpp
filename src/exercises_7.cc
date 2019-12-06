#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include "util.hh"

using std::cout;
using std::endl;
using std::map;
using std::istream;
using std::cin;
using std::string;
using std::stringstream;
using std::vector;


// Group all words that occur once, then all words that occur twice, etc.
// How would we do this?
// Reconstruct post hoc.
void ex7_1(istream& input) {
    string s;
    map<string, int> counters;

    while (input >> s)
        ++counters[s];

    typedef map<string, int>::const_iterator iter;

    for (iter it = counters.begin(); it != counters.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
}


int main() {
    std::cout << "Hello, world!" << std::endl;

    string s = "It was the best of times, it was the worst of times";
    stringstream sin1(s);
    ex7_1(sin1);

    return 0;
}
