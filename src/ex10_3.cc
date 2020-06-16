#include <iostream>
#include <algorithm>
#include <vector>
#include "ex10_3.hh"
#include "util.hh"

using std::vector;
using std::cout;
using std::endl;
using std::sort;

int main() {
    cout << "Starting." << endl;

    vector<double> inputs = {1.5, -10, 10, 2, 1,  3};
    print_vector_double(inputs);
    double fm1 = generic_median(inputs.begin(), inputs.end());
    cout << "Generic median (vector) was " << fm1 << endl;
    print_vector_double(inputs);


    double array_inputs[] = {1.5, -10, 10, 2, 1,  3};
    int inputs_length = sizeof(array_inputs) / sizeof(*array_inputs);
    double fm2 = generic_median(array_inputs, array_inputs + inputs_length);
    cout << "Generic median (array) was " << fm2 << endl;

    cout << "End." << endl;
    return 0;
}
