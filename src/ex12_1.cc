#include <iostream>
#include <list>
#include "ex12_1.hh"

using std::cin;
using std::cout;
using std::endl;
using std::list;

void demo_assignment_operator() {
    cout << "Assignment" << endl;
    StrV name1("Dave");
    StrV name2;
    name2 = name1;

    cout << "Type something (not Dave): ";
    cin >> name1;

    cout << "name1 is " << name1 << endl;
    cout << "name2 is " << name2 << endl;
}

int main() {
    cout << "Starting." << endl;
    
    StrV foo("hello world");
    cout << foo << endl;

    StrV empty;
    cout << "Empty string: '" << empty << "'" << endl;

    StrV filled_string(7, 'z');

    cout << "Filled string: '" << filled_string << "'" << endl;


    list<char> source = {'h', 'e', 'l', 'l', 'o'};
    StrV copied_string(source.begin(), source.end());


    cout << "Copied from container: '" << copied_string << "'" << endl;


    cout << "Index non-const StrV: '" << foo[3] << "'" << endl;

    StrV const c_str_v("hello universe");
    cout << "Index const StrV: '" << c_str_v[6] << "'" << endl;

    StrV s_implicit_conversion = "hello world";
    cout << "Implicit conversion: '" << s_implicit_conversion << "'" << endl;


    cout << "Demo overloaded iostream operators." << endl;
    cout << "Please type: ";
    StrV si;
    cin >> si;
    cout << "Read string as: '" << si << "'" << endl;

    // cout << "Addition/assignment" << endl;

    // StrV s7("Foo bar");
    // StrV s8("baz");

    // s7 += s8;

    // cout << "Concatenated value was " << s7 << endl;


    // cout << "Regular addition" << endl;

    // StrV s9("foo bar ");
    // StrV s10("baz");

    // StrV s11 = s9 + s10;

    // cout << "Added value was " << s11 << endl;

    // cout << "Mixed-type expressions" << endl;
    // StrV name("Dave");
    // const StrV greeting = "Hello, " + name + "!";

    // cout << greeting << endl;


    demo_assignment_operator();



    cout << "Copy constructor" << endl;
    StrV name1("Dave");
    StrV name2 = name1;

    cout << "Type something (not Dave): ";
    cin >> name1;

    cout << "name1 is " << name1 << endl;
    cout << "name2 is " << name2 << endl;

    cout << "End." << endl;
    return 0;
}
