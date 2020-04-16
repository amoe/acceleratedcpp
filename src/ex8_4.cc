#include <iostream>
#include <algorithm>
#include "util.hh"

using std::swap;
using std::cout;
using std::endl;

// March begin forward and end backwards.

// When begin is at index 0, end is at index 4.
// End gradually gets less, so the algorithm stops in the middle.
// You must use swap because there are two assignments.

template <class T>
void my_correct_reverse(T begin, T end) {
    while (begin != end) {
        --end;
        if (begin != end) {
            swap(*begin, *end);
            begin++;
        }
    }
}

template <class T>
void my_incorrect_reverse(T begin, T end) {
    while (begin != end) {
        --end;
        if (begin != end) {
            // This works...
            *begin = *end;
            // But this doesn't because *begin has already been overwritten.
            *end = *begin;
            begin++;
        }
    }
}


int main() {
    cout << "Starting." << endl;

    cout << "Correct reverse:" << endl;
    vector<int> vec1 = {1,2,3,4,5};
    my_correct_reverse(vec1.begin(), vec1.end());
    print_vector_int(vec1);

    // The elements behind the midpoint are never modified when we
    // use the incorrect version without swap.
    cout << "Incorrect reverse:" << endl;
    vector<int> vec2 = {1,2,3,4,5};
    my_incorrect_reverse(vec2.begin(), vec2.end());
    print_vector_int(vec2);

    cout << "End." << endl;
    return 0;
}
