#include <iostream>

using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    int x = 5;
    int* p = &x;

    cout << "x = " << x << endl;

    cout << "End." << endl;
    return 0;
}
