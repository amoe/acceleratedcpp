#include "util.hh"

using std::cout;
using std::endl;

void print_vector(const vector<string>& vec) {
    for (string item: vec) {
        cout << '"' << item << '"' << endl;
    }
}
