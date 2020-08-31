#include <iostream>
#include <vector>
#include <string>
#include "ex12_11.hh"

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Koenig&Moo's index-based string split.
vector<StrV> split(const StrV& s) {
    vector<string> result;
    typedef StrV::size_type str_sz;
    str_sz i = 0;

    while (i < s.size()) {
        // skip leading spaces
        while (isspace(s[i]) && i < s.size())
            i++;

        str_sz j = i;
        while (!isspace(s[j]) && j < s.size())
            j++;


        if (j != i) {
            str_sz n_chars = j - i;
            result.push_back(s.substr(i, n_chars));
            i = j;
        }
    }

    return result;
}


int main() {
    cout << "Starting." << endl;
    
    StrV foo("The quick brown fox jumped over the lazy dog");

    using iter_t = vector<string>::const_iterator;
    vector<string> result = split(foo);

    for (iter_t it = result.begin(); it != result.end(); it++) {
        std::cout << *it << std::endl;
    }

    cout << "End." << endl;
    return 0;
}
