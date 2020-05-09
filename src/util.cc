#include <map>
#include "util.hh"

using std::map;
using std::cout;
using std::endl;

void print_vector(const vector<string>& vec) {
    for (string item: vec) {
        cout << '"' << item << '"' << endl;
    }
}

void print_vector_int(const vector<int>& vec) {
    for (int item: vec) {
        cout << item << endl;
    }
}

void print_vector_double(const vector<double>& vec) {
    for (double item: vec) {
        cout << item << endl;
    }
}

void print_list(const list<string>& lst) {
    for (string item: lst) {
        cout << '"' << item << '"' << endl;
    }
}

void print_map_int_string(const map<int, string>& m) {
    using iter_t = map<int, string>::const_iterator;
    for (iter_t it = m.begin(); it != m.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }
}
