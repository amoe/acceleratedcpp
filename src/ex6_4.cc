#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::copy;

void print_vector(vector<int> arg) {
    for (int i : arg) {
        std::cout << i << ", ";
    }

    std::cout << std::endl;
}

// grow vector with insert()
void approach1() {
    vector<int> u(10, 100);
    vector<int> v;

    print_vector(u);
    v.insert(v.end(), u.begin(), u.end());
    print_vector(v);
}

// preallocate vector to known size
void approach2() {
    vector<int> u(10, 100);
    vector<int> v(10);

    print_vector(u);
    copy(u.begin(), u.end(), v.begin());
    print_vector(v);
}


// slightly ridiculous approach (might even work at compile time?) but still
// works
void approach3() {
    vector<int> u(10, 100);
    vector<int> v(u);

    print_vector(u);
    print_vector(v);
}



int main() {
    approach1();
    approach2();
    approach3();

    return 0;
}
