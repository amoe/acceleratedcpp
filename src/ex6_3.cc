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

int main() {
    vector<int> u(10, 100);
    vector<int> v;

    print_vector(u);
    copy(u.begin(), u.end(), v.begin());
    print_vector(v);

    return 0;
}
