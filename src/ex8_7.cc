#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::max;

int main() {
    cout << "Starting." << endl;

    int value1 = 41;
    int value2 = 43;

    int result = max(value1, value2);
    
    cout << "The maximum is " << result << endl;

    cout << "End." << endl;
    return 0;
}
