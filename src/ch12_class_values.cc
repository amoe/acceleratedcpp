#include <iostream>
#include <cstring>
#include <iterator>
#include <list>
#include "vec.hh"
#include "ch12_class_values.hh"


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

    cout << "End." << endl;
    return 0;
}
