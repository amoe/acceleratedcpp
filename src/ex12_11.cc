#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "ex12_11.hh"

using std::list;
using std::find_if;
using std::cout;
using std::endl;
using std::vector;

// Koenig&Moo's index-based string split.
vector<Str> ch5_split(const Str& s) {
    vector<Str> result;
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

bool space(char c) { return isspace(c); }
bool not_space(char c) { return !isspace(c); }

vector<Str> ch6_split(const Str& str) {
    typedef Str::const_iterator iter;
    vector<Str> ret;

    iter i = str.begin();
    while (i != str.end()) {
        // get the start of the range
        i = find_if(i, str.end(), not_space);

        // get the end of the range
        iter j = find_if(i, str.end(), space);
        
        if (i != str.end()) {
            ret.push_back(Str(i, j));
        }

        // jump ahead to the end of the range
        i = j;
    }

    return ret;
}

void test_substr() {
    Str foo("The quick brown fox jumped over the lazy dog");
    Str result = foo.substr(1, 2);
    cout << "result was '" << result << "'" << endl;
}

void test_ch5_split() {
    Str foo("The quick brown fox jumped over the lazy dog");
    using iter_t = vector<Str>::const_iterator;
    vector<Str> components = ch5_split(foo);

    for (iter_t it = components.begin(); it != components.end(); it++) {
        std::cout << *it << std::endl;
    }
}

void test_ch6_split() {
    Str foo("The quick brown fox jumped over the lazy dog");
    using iter_t = vector<Str>::const_iterator;
    vector<Str> components = ch6_split(foo);

    for (iter_t it = components.begin(); it != components.end(); it++) {
        std::cout << *it << std::endl;
    }
}


int main() {
    cout << "Starting." << endl;

    test_substr();
    test_ch5_split();
    test_ch6_split();

    cout << "End." << endl;
    return 0;
}
