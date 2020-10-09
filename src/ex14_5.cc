#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "handles.hh"
#include "ex14_5.hh"

using std::cout;
using std::endl;
using std::find_if;
using std::istream;
using std::list;
using std::max;
using std::ostream;
using std::stringstream;
using std::strlen;
using std::vector;


/*
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
*/

void test_substr() {
    Str foo("The quick brown fox jumped over the lazy dog");
    Str result = foo.substr(1, 2);
    cout << "result was '" << result << "'" << endl;
}

/*

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

Str::size_type width(const vector<Str>& v) {
    Str::size_type maxlen = 0;

    for (vector<Str>::size_type i = 0; i < v.size(); i++) {
        maxlen = max(maxlen, v[i].size());
    }

    return maxlen;
}


vector<Str> frame(const vector<Str>& words) {
    vector<Str> result;
    Str::size_type maxlen = width(words);
    Str border(maxlen + 4, '*');

    result.push_back(border);

    for (vector<Str>::size_type i = 0; i < words.size(); i++) {
        Str padding(maxlen - words[i].size(), ' ');
        
        result.push_back("* "  + words[i] + padding + " *");
    }

    result.push_back(border);

    return result;
}

vector<Str> vcat(const vector<Str>& top, const vector<Str>& bottom) {
    vector<Str> result = top;

    for (
        vector<Str>::const_iterator iter = bottom.begin();
        iter != bottom.end();
        iter++
    ) {
        result.push_back(*iter);
    }

    return result;
}

vector<Str> hcat(const vector<Str>& left, const vector<Str>& right) {
    vector<Str> result;

    Str::size_type widthLeft = width(left) + 1;
    // i will track the rows of left, j the rows of right
    vector<Str>::size_type i = 0, j = 0;

    while (i != left.size() || j != right.size()) {
        Str s;

        // i may have already run out at any stage during the loop.
        if (i != left.size()) {
            s = left[i];
            i++;
        }

        s += Str(widthLeft - s.size(), ' ');

        if (j != right.size()) {
            s += right[j];
            j++;
        }

        
        result.push_back(s);
    }

    return result;
}

void test_frame() {
    vector<Str> result;

    result.push_back("The");
    result.push_back("quick");
    result.push_back("brown");
    result.push_back("fox");
    result.push_back("jumped");
    result.push_back("over");
    result.push_back("the");
    result.push_back("lazy");
    result.push_back("dog");

    using iter_t = vector<Str>::const_iterator;

    vector<Str> r1 = frame(result);
    for (iter_t it = r1.begin(); it != r1.end(); it++) {
        std::cout << *it << std::endl;
    }

    vector<Str> r2 = vcat(result, r1);
    for (iter_t it = r2.begin(); it != r2.end(); it++) {
        std::cout << *it << std::endl;
    }

    vector<Str> r3 = hcat(result, r1);
    for (iter_t it = r3.begin(); it != r3.end(); it++) {
        std::cout << *it << std::endl;
    }
}
*/


int main() {
    cout << "Starting." << endl;

    test_substr();
    // test_ch5_split();
    // test_ch6_split();
    // test_frame();

    cout << "End." << endl;
    return 0;
}
