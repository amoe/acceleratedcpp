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


    vector<double> scores2 = {0.0, 1.0, 1.8, 1.0};

    int sum2 = accumulate(scores2.begin(), scores2.end(), 0);

    cout << "Sum2 was " << sum2 << endl;


    return 0;
}
