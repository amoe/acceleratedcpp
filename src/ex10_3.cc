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
    double fm1 = generic_median<double>(inputs.begin(), inputs.end());
    cout << "Generic median (vector) was " << fm1 << endl;
    print_vector_double(inputs);

    cout << "Starting to test array case." << endl;

    double array_inputs[] = {1.5, -10, 10, 2, 1,  3};
    int inputs_length = sizeof(array_inputs) / sizeof(*array_inputs);
    for (int i = 0; i < inputs_length; i++) { cout << array_inputs[i] << endl; }
    double fm2 = generic_median<double>(array_inputs, array_inputs + inputs_length);
    cout << "Generic median (array) was " << fm2 << endl;
    for (int i = 0; i < inputs_length; i++) { cout << array_inputs[i] << endl; }

    cout << "End." << endl;
    return 0;
}
