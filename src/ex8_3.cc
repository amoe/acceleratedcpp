#include <iostream>
#include <vector>
#include <algorithm>
#include "util.hh"

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

    vector<double> numbers = {9,4,3,2,7,6,5,1};

    double result = median(numbers);
    
    cout << "Median was: " << result << endl;

    cout << "End." << endl;
    return 0;
}
