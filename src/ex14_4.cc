#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include "handles.hh"
#include "ex14_4.hh"

using std::ostream;
using std::back_inserter;
using std::vector;
using std::istream;
using std::stringstream;
using std::strlen;
using std::cout;
using std::endl;

class Str {
    friend istream& operator>>(istream&, Str&);
    
public:
    Str& operator+=(const Str& s) {
        data.make_unique();
        copy(s.data->begin(), s.data->end(), back_inserter(*data));
        return *this;
    }

    Str(const char* cp): data(new vector<char>) {
        size_t length = strlen(cp);
        copy(cp, cp + length, back_inserter(*data));
    }

    using size_type = vector<char>::size_type;

    size_type size() const {
        return data->size();
    }

    // Because this can be used as an lvalue, we must call make_unique.
    // Note that char& is now a reference.
    char& operator[](size_type i) {
        data.make_unique();
        return (*data)[i];
    }

    const char operator[](size_type i) const {
        return (*data)[i];
    }

    int get_refcount() const {
        return data.get_refcount();
    }

    
private:
    ControllableHandle<vector<char>> data;
};

Str operator+(const Str& x, const Str& y) {
    Str result = x;
    result += y;
    return result;
}

ostream& operator<<(ostream& os, const Str& s) {
    for (Str::size_type i = 0; i < s.size(); i++) {
        os << s[i];
    }
    return os;
}

istream& operator>>(istream& is, Str& s) {
    s.data.make_unique();
    s.data->clear();
    char c;

    bool last_char_space = true;
    
    while (is.get(c) && isspace(c)) {
    }

    if (is) {
        do {
            s.data->push_back(c);
        } while (is.get(c) && !isspace(c));

        if (is) {
            is.unget();
        }
    }

    return is;
}

void str_test() {
    Str name = "Dave";
    Str greeting = "Hello, " + name + "!";
    cout << "Greeting is now: '" + greeting + "'" << endl;
}

void str_test_compound_concatenation() {
    Str name1 = "Dave";
    cout << "Refcount is " << name1.get_refcount() << endl;
    Str name2 = name1;    // Should not copy.
    cout << "Refcount is " << name1.get_refcount() << endl;

    name1 += " Lister";
    cout << "Name1 is now '" << name1 << "'" << endl;
    cout << "Name2 is now '" << name2 << "'" << endl;

    cout << "Refcount of name1 is " << name1.get_refcount() << endl;
    cout << "Refcount of name2 is " << name2.get_refcount() << endl;
}

void str_test_lvalue_subscript() {
    Str name1 = "Dave";
    Str name2 = name1;

    name1[1] = 'i';

    cout << "Name1 is now: '" << name1 << "'" << endl;
    cout << "Name2 is now: '" << name2 << "'" << endl;
}

void str_test_input() {
    Str s1("Dave");
    Str s2 = s1;
    stringstream ss_val(" Lister");
    ss_val >> s1;

    cout << "s1 is now " << s1 << endl;
    cout << "s2 is now " << s2 << endl;
}

int main() {
    cout << "Starting." << endl;

    str_test();
    str_test_compound_concatenation();
    str_test_lvalue_subscript();
    str_test_input();
    
    cout << "End." << endl;
    return 0;
}
