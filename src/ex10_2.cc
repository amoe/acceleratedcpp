#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::sort;

double median(vector<double> vec) {
    typedef vector<double>::size_type vec_sz;
    
    vec_sz size = vec.size();
    if (size == 0)
        throw std::domain_error("cannot take the median of an empty vector");

     sort(vec.begin(), vec.end());

     vec_sz mid = size / 2;

    if  ((size % 2) == 0) {
        return (vec[mid] + vec[mid-1]) / 2;
    } else {
        return vec[mid];
    }
}


int main() {
    cout << "Starting." << endl;

    vector<double> foo = {-10, 1, 1.5, 2, 3, 10};
    
    double found_median = median(foo);

    // should be 1.75
    cout << "The median was " << found_median << endl;

    cout << "End." << endl;
    return 0;
}
