#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <sstream>
#include <iterator>
#include "util.hh"
#include "split.hh"

using std::accumulate;
using std::string;
using std::sort;
using std::vector;
using std::cout;
using std::endl;
using std::domain_error;
using std::stringstream;
using std::istream_iterator;
using std::ostream_iterator;

const string multi_line_input = R"(
5
4
3
2
1
42
)";


template <class T, class U>
bool my_binary_search(T begin, T end, const U& value) {
    while (begin < end) {
        T midpoint = begin + ((end - begin) / 2);
        U midpoint_value = *midpoint;    // Not totally sure about the type here.

        if (midpoint_value > value) {
            end = midpoint;
        } else if (midpoint_value < value) {
            begin = midpoint + 1;
        } else {
            return true;
        }        
    }

    return false;
}

// Requires a bidirectional iterator.
template <class T>
void my_reverse(T begin, T end) {
    while (begin != end) {
        --end;
        if (begin != end) {
            swap(*begin++, *end);
        }
    }
}

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

template <typename T>
T zero() {
    return 0;
}

void demo_stream_iterator_input() {
    vector<int> v;

    stringstream sin1(multi_line_input);
    istream_iterator<int> my_stream_iterator(sin1);
    istream_iterator<int> sentinel;

    copy(my_stream_iterator, sentinel, back_inserter(v));

    using iter_t = vector<int>::const_iterator;
    for (iter_t it = v.begin(); it != v.end(); it++) {
        cout << "'" << *it << "'" << endl;
    }
}

void demo_stream_iterator_output() {
    vector<int> v = {3, 5, 2, 27};

    // construct output stream iterator using a sentinel
    ostream_iterator<int> my_stream_iterator(cout, " ");

    copy(v.begin(), v.end(), my_stream_iterator);

    cout << endl;
}

void demo_using_iterator_split() {
    string foo = "the quick brown fox jumped over the lazy dog";
    vector<string> result;


    split_to_iterator(foo, back_inserter(result));
    print_vector(result);
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

    my_reverse(haystack.begin(), haystack.end());

    print_vector(haystack);

    vector<int> h1 = {0, 1, 2, 3, 4, 5};

    bool found = my_binary_search(h1.begin(), h1.end(), 3);

    cout << "Found 3: " << found << endl;

    bool found2 = my_binary_search(h1.begin(), h1.end(), 10);

    cout << "Found 10: " << found2 << endl;

    demo_stream_iterator_input();
    demo_stream_iterator_output();

    demo_using_iterator_split();

    // demo explicit hinting of template value.
    double foo = zero<double>();

    return 0;
}
