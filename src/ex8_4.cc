#include <iostream>
#include <algorithm>
#include "util.hh"

using std::swap;
using std::cout;
using std::endl;

template <class T>
void my_reverse(T begin, T end) {
    while (begin != end) {
        --end;
        if (begin != end) {
            swap(*begin++, *end);
        }
    }
}


int main() {
    cout << "Starting." << endl;

    vector<int> vec = {1,2,3,4,5};

    my_reverse(vec.begin(), vec.end());

    print_vector_int(vec);

    cout << "End." << endl;
    return 0;
}
