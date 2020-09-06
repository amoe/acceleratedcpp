#include <iostream>
#include <string>
#include "ex12_14.hh"

using std::string;
using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    // 12-14. Write a program to initialize a Vec from a string .
    
    string content = "Hello, world!";

    Vec<char> some_vector(content.begin(), content.end());

    using iter_t = Vec<char>::const_iterator;
    for (iter_t it = some_vector.begin(); it != some_vector.end(); it++) {
        cout << *it;
    }

    cout << endl;

    cout << "End." << endl;
    return 0;
}
