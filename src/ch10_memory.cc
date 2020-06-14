#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstring>

using std::strlen;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::vector;
using std::back_inserter;
using std::copy;
using std::cout;
using std::endl;
using std::string;

// K&M implementation of strcpy() with C++ primitives.
char* duplicate_chars(const char* p) {
    size_t length = strlen(p) + 1;
    char* result = new char[length];
    copy(p, p + length, result);
    return result;
}

void demo_dyncopy() {
    const char* s1 = "foobar";
    char* s2 = duplicate_chars(s1);
    cout << "Original string is " << s1 << endl;
    cout << "New string is " << s2 << endl;

    // Demonstrate that it was actually copied by changing it
    s2[2] = 'b';
    cout << "Original string is " << s1 << endl;
    cout << "New string is " << s2 << endl;

    // Caller must delete after use!
    delete s2;
}

void demo_newdelete() {
    // Dynamic allocation examples
    int* p = new int(42);

    cout << "P was initialized to " << *p << endl;

    ++*p;

    cout << "P was updated to " << *p << endl;

    delete p;
}

void copyfile(string input_path) {
    cout << "Reading from '" << input_path << "'" << endl;

    // Only works in C++11, otherwise need to coerce with .c_str()
    ifstream infile(input_path);
    ofstream outfile("/dev/null");

    string s;
    
    while (getline(infile, s)) {
        outfile << s << endl;
    }
}

void catfiles(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        char* this_path = argv[i];
        ifstream infile(this_path);

        if (!infile) {
            cerr << "cannot open file " << this_path << endl;
            continue;
        }

        string line;
        while (getline(infile, line)) {
            cout << line << endl;
        }
    }
}

string letter_grade(double grade) {
    // grading thresholds
    static const double numbers[] = {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };

    cout << "Sizeof numbers is " << sizeof(numbers) << endl;
    cout << "Sizeof numbers pointer is " << sizeof(&numbers) << endl;

    // ??? Not really clear how to read this definition.  What part of the
    // declaration refers to what part of the type?
    // Second const refers to the pointer.  First const refers to the type
    // behind the pointer.

    static const char* const letters[] = {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
    };

    // Calculate the number of elements in the array -- we divide the size
    // of the whole array by the size of the first element.  Pretty sure
    // this happens at compile time.
    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);


    for (size_t i = 0; i < ngrades; i++) {
        if (grade >= numbers[i])
            return letters[i];
    }

    return "?";
}

int square(int x) {
    return x * x;
}

size_t my_strlen(const char* p) {
    size_t result = 0;
    while (*p != '\0') {
        result++;
        p++;
    }
    return result;
}

int faux_main(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        char* this_string = argv[i];
        cout << this_string << " ";
    }

    cout << endl;
    return 0;
}

int main() {
    cout << "Starting." << endl;

    // Basic pointers
    int x = 5;
    int* p = &x;

    cout << "x = " << x << endl;

    *p = 6;
    cout << "x = " << x << endl;



    // Function pointers
    int (*fp)(int);

    fp = square;

    int result = fp(4);

    cout << "result (call-through-pointer) is " << result << endl;


    // Copy through array
    vector<double> dv;
    const int number_of_dimensions = 3;
    double coords[number_of_dimensions] = {4,5,6};
    copy(
        coords,   // Has a pointer type
        coords + 3,  // Is still usable for comparisons
        back_inserter(dv)
    );


    using iter_t = vector<double>::const_iterator;
    for (iter_t it = dv.begin(); it != dv.end(); it++) {
        cout << *it << endl;
    }

    // Construct from pointer

    vector<double> dv2(coords, coords + 3);
    using iter_t = vector<double>::const_iterator;
    for (iter_t it = dv2.begin(); it != dv2.end(); it++) {
        cout << *it << endl;
    }

    // Create array without specifying length.
    const int month_lengths[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    


    // String literals are just nul-terminated arrays.
    const char hello[] = {'H', 'e', 'l', 'l', 'o', '\0'};

    cout << "This is a C-style string: " << hello << endl;

    cout << "Length is " << my_strlen(hello) << endl;

    string s(hello);

    cout << "This is a C++ string: " << s << endl;

    // Construct a string from two iterators
    string s2(hello, hello + my_strlen(hello));
    cout << "This is another C++ string: " << s2 << endl;

    string grade_result = letter_grade(95);
    cout << "Grade was " << grade_result << endl;

    // warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]
    char* args[] = {"fry", "bender", "leela"};
    faux_main(3, args);


    cout << "Copy file demo." << endl;
    copyfile("/etc/hosts");

    char* cat_args[] = {"/etc/hosts", "/etc/nonexistenshit", "/etc/issue"};
    catfiles(2, cat_args);

    demo_newdelete();

    demo_dyncopy();


    cout << "End." << endl;
    return 0;
}
