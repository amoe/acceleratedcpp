#include <iostream>
#include <vector>
#include <algorithm>
#include "util.hh"

using std::cout;
using std::endl;
using std::vector;
using std::sort;

using iter_t = vector<double>::iterator;

// MUTATES ITS ARGUMENT; iterators are required to be random-access iterators.
double median_f(iter_t b, iter_t e) {
    typedef vector<double>::size_type vec_sz;
    
    vec_sz size = e - b;
    if (size == 0)
        throw std::domain_error("cannot take the median of an empty vector");

    sort(b, e);

    vec_sz mid = size / 2;

    if ((size % 2) == 0) {
        double x = *(b + (mid - 1));
        double y = *(b + mid);
        return (x + y) / 2;
    } else {
        return *(b + mid);
    }
}


int main() {
    cout << "Starting." << endl;

    

    vector<double> numbers = {9,4,3,2,7,6,5,1};

    double result = median_f(numbers.begin(), numbers.end());
    
    cout << "Median was: " << result << endl;

    cout << "Caller's vector is now:" << endl;
    print_vector_double(numbers);

    cout << "End." << endl;
    return 0;
}
