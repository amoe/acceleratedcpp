#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

void print_vector(const vector<string>& vec) {
    for (string item: vec) {
        cout << item << endl;
    }
}

void demo_extend_vector() {
    vector<string> myvec = {"hello", "world"};

    vector<string> myvec2 = {"leela", "fry"};

    // Extend myvec with all elements of myvec2
    myvec.insert(myvec.end(), myvec2.begin(), myvec2.end());


    print_vector(myvec);
}

int main() {
    demo_extend_vector();

    cout << "hello world" << endl;
}
