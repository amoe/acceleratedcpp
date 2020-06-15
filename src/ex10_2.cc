#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

using std::domain_error;
using std::cout;
using std::endl;
using std::vector;
using std::sort;

double array_median(double* numbers, size_t numbers_length) {
    if (numbers_length == 0) {
        throw domain_error("no sensible median");
    }

    sort(numbers, numbers + numbers_length);

    size_t mid = numbers_length / 2;

    if ((numbers_length % 2) == 0) {
        return (numbers[mid] + numbers[mid - 1]) / 2;
    } else {
        return numbers[mid];
    }
}

double vector_median(vector<double> vec) {
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

void test_vector_median() {
    // should be 1.75
    vector<double> inputs = {-10, 1, 1.5, 2, 3, 10};
    double found_median = vector_median(inputs);
    cout << "Vector median was " << found_median << endl;
}

void test_array_median() {
    double inputs[] = {1.5, -10, 10, 2, 1,  3};
    int inputs_length = sizeof(inputs) / sizeof(*inputs);
    double found_median = array_median(inputs, inputs_length);
    cout << "Array median was " << found_median << endl;
}


int main() {
    cout << "Starting." << endl;

    test_vector_median();
    test_array_median();

    cout << "End." << endl;
    return 0;
}
