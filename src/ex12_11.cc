#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "ex12_11.hh"

using std::list;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// Koenig&Moo's index-based string split.
/*
vector<Str> split(const Str& s) {
    vector<string> result;
    typedef Str::size_type str_sz;
    str_sz i = 0;

    while (i < s.size()) {
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
*/

int main() {
    cout << "Starting." << endl;
    
    Str foo("The quick brown fox jumped over the lazy dog");
    Str result = foo.substr(1, 2);

    cout << "result was '" << result << "'" << endl;

    /*
    using iter_t = vector<string>::const_iterator;
    vector<string> result = split(foo);

    for (iter_t it = result.begin(); it != result.end(); it++) {
        std::cout << *it << std::endl;
    }

    cout << "End." << endl;
    return 0;
    */
}
