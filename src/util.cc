#include "util.hh"

using std::cout;
using std::endl;

void print_vector(const vector<string>& vec) {
    for (string item: vec) {
        cout << '"' << item << '"' << endl;
    }
}

void print_list(const list<string>& lst) {
    for (string item: lst) {
        cout << '"' << item << '"' << endl;
    }
}
