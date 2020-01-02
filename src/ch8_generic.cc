#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

using std::accumulate;
using std::string;
using std::sort;
using std::vector;
using std::cout;
using std::endl;
using std::domain_error;


// An implementation of std::find.
template <class T, class X>
T my_find(T begin, T end, const X& x) {
    while (begin != end && *begin != x) {
        ++begin;
    }

    return begin;
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

    return 0;
}
