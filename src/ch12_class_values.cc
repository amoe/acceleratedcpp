#include <iostream>
#include <cstring>
#include <iterator>
#include <list>
#include "vec.hh"
#include "ch12_class_values.hh"

using std::cin;

int main() {
    cout << "Starting." << endl;

    list<char> foo = {'h', 'e', 'l', 'l', 'o'};

    Str s1;   // Blank string
    Str s2("hello world");    // Char* constructor
    Str s3(8, 'f');
    Str s4(foo.begin(), foo.end());

    cout << "s1: ";
    s1.print();

    cout << "s2: ";
    s2.print();

    cout << "s3: ";
    s3.print();

    cout << "s4: ";
    s4.print();


    cout << "s5: ";
    // User defined conversion.
    // Implicitly calls the same constructor as s2.
    Str s5 = "foo bar";
    s5.print();

    char my_char = 'z';
    cout << "xy" << my_char << my_char << "y" << endl;

    char c2 = s2[6];
    cout << c2 << c2 << c2 << endl;

    Str s6;
    cin >> s6;

    cout << "End." << endl;
    return 0;
}
