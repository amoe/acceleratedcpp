#ifndef SPLIT_HH
#define SPLIT_HH

#include <vector>
#include <string>
#include <algorithm>
#include "characters.hh"

using std::vector;
using std::string;
using std::find_if;

vector<string> split(const string& str);

// A generalized split that works using output iterators.
template <typename T>
void split_to_iterator(const string& str, T output) {
    using iter_t = string::const_iterator;

    iter_t i = str.begin();

    while (i != str.end()) {
        i = find_if(i, str.end(), not_space);
        iter_t j = find_if(i, str.end(), space);
        
        if (i != str.end()) {
            *output = string(i, j);
            output++;
        }

        i = j;
    }
}


#endif /* SPLIT_HH */
