#include <iostream>
#include <list>
#include "ex12_1.hh"

using std::cin;
using std::cout;
using std::endl;
using std::list;

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

    cout << "End." << endl;
    return 0;
}
