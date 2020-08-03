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

    cout << "Demo overloaded iostream operators." << endl;
    cout << "Please type: ";

    Str s6;
    cin >> s6;

    cout << "Read string as: " << s6 << endl;
    cout << "About to write a string: " << s2 << endl;

    cout << "Addition/assignment" << endl;

    Str s7("Foo bar");
    Str s8("baz");

    s7 += s8;

    cout << "Concatenated value was " << s7 << endl;

    cout << "Regular addition" << endl;

    Str s9("foo bar ");
    Str s10("baz");

    Str s11 = s9 + s10;

    cout << "Added value was " << s11 << endl;

    cout << "End." << endl;


    cout << "Mixed-type expressions" << endl;
    Str name("Dave");
    const Str greeting = "Hello, " + name + "!";

    cout << greeting << endl;

    return 0;
}
