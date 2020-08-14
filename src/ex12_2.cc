#include <iostream>
#include <list>
#include "ex12_2.hh"

using std::list;
using std::cout;
using std::endl;

int main() {
    cout << "Starting." << endl;

    StrV foo("Hello, world!");
    cout << foo << endl;

    const char* c_str_ptr = foo.c_str();

    cout << (int) c_str_ptr[13] << endl;
    cout << c_str_ptr << endl;

    list<char> source = {'h', 'e', 'l', 'l', 'o'};
    StrV copied_string(source.begin(), source.end());
    cout << "Copied from container: '" << copied_string << "'" << endl;
    cout << "Size is " << copied_string.size() << endl;


    StrV filled_string(7, 'z');
    cout << "Filled string: '" << filled_string << "'" << endl;

    StrV empty;
    cout << "Size of empty string: " << empty.size() << endl;
    cout << "Contents of empty string: '" << empty.c_str() << "'" << endl;
    

    StrV empty2;
    const char* empty_ptr = empty2.data();
    // For some reason it's still null-terminated in practice, but
    // I think this is undefined behaviour.
    cout << "Value of empty string is " << (int) *empty_ptr << endl;

    
    char my_buffer[5];
    foo.copy(my_buffer, 5);

    // Because copy doesn't null terminate, we can't just cout
    // the buffer to print it.
    for (int i = 0; i < 5; i++) {
        cout << my_buffer[i];
    }
    cout << endl;

    cout << "End." << endl;
    return 0;
}
