#include <iostream>
#include <vector>
#include "ex8_8.hh"

using std::cout;
using std::endl;
using std::vector;

int main() {
    cout << "Starting." << endl;
    vector<int> vec1 = {5,10,15,20,25,30,35,40};

    bool result1 = binary_search(vec1.begin(), vec1.end(), 15);

    cout << "Found 15: " << (result1 ? "yes" : "no") << endl;

   bool result2 = binary_search(vec1.begin(), vec1.end(), 45);

   cout << "Found 45: " << (result2 ? "yes" : "no") << endl;

    cout << "End." << endl;
    return 0;
}
