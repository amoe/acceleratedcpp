#include <vector>
#include "ex10_2.hh"

using std::vector;

int main() {
    cout << "Starting." << endl;

    vector<double> foo = {-10, 1, 1.5, 2, 3, 10};
    
    double found_median = median(foo);

    // should be 1.75
    cout << "The median was " << found_median << endl;

    cout << "End." << endl;
    return 0;
}
