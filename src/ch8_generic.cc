#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include "util.hh"

using std::accumulate;
using std::string;
using std::sort;
using std::vector;
using std::cout;
using std::endl;
using std::domain_error;

// Requires a forward iterator
template <class T, class U>
void my_replace(T begin, T end, const U& old_value, const U& new_value) {
    while (begin != end) {
        if (*begin == old_value) {
            *begin = new_value;
        }

        begin++;
    }
}

// Requires an input iterator.
template <class T, class X>
T my_find(T begin, T end, const X& x) {
    while (begin != end && *begin != x) {
        ++begin;
    }

    return begin;
}

// Requires an output iterator in its third argument.
template <class T, class U>
U my_copy(T begin, T end, U destination) {
    while (begin != end) {
        *destination++ = *begin++;
    }
    return destination;
}


template <class T>
T median(vector<T> v) {
    typedef typename vector<T>::size_type vec_sz;

    vec_sz size = v.size();
    if (size == 0) {
        throw domain_error("median of an empty vector");
    }

    sort(v.begin(), v.end());

    vec_sz mid = size / 2;

    // With an even number of observations, the median should be the
    // mean of the two middle values.
    if (size % 2 == 0) {
        return (v[mid] + v[mid - 1]) / 2;
    } else {
        return v[mid];
    }
}

int main() {
    cout << "Starting." << endl;

    vector<int> scores = {5, 1, 3};

    int median_value = median(scores);

    cout << "Median value was " << median_value << endl;

    cout << "End." << endl;

    int sum = accumulate(scores.begin(), scores.end(), 0);
    cout << "Sum was " << sum << endl;

    vector<double> scores2 = {0.0, 1.0, 1.8, 1.0};

    int sum2 = accumulate(scores2.begin(), scores2.end(), 0);

    cout << "Sum2 was " << sum2 << endl;


    vector<string> haystack = {"fry", "bender", "leela"};

    using iter_t = vector<string>::const_iterator;

    iter_t it1 = haystack.begin();
    iter_t it2 = haystack.end();

    cout << "it1 points at " << *it1 << endl;

    iter_t result = my_find(it1, it2, "bender");

    cout << "result iterator points at " << *result << endl;

    vector<string> target(haystack.size());
    my_copy(haystack.begin(), haystack.end(), target.begin());
    print_vector(target);
    cout << target.size() << endl;

    print_vector(haystack);

    // Using char will fail here, we must explicitly coerce to string.
    my_replace(haystack.begin(), haystack.end(), string("bender"), string("Hedonism-Bot"));

    print_vector(haystack);

    return 0;
}
