#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "grade.hh"
#include "student_info.hh"
#include "util.hh"

using std::streamsize;
using std::setprecision;
using std::max;
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
    typedef map<string, int>::const_iterator iter1_t;
    typedef map<int, vector<string>>::const_iterator iter2_t;
    string s;
    map<string, int> counters;

    while (input >> s)
        ++counters[s];

    map<int, vector<string>> grouped;

    // Basically invert the map
    for (iter1_t it = counters.begin(); it != counters.end(); ++it) {
        string word = it->first;
        int occurrences = it->second;

        grouped[occurrences].push_back(word);
    }

    for (iter2_t it = grouped.begin(); it != grouped.end(); ++it) {
        int occurrences = it->first;
        cout << "Occurrences: " << occurrences << endl;
        print_vector(it->second);
    }
}


int main() {
    std::cout << "Hello, world!" << std::endl;

    string s = "It was the best of times, it was the worst of times";
    stringstream sin1(s);
    ex7_1(sin1);

    return 0;
}
