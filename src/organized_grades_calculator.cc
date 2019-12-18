#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <iomanip>

using std::vector;
using std::sort;
using std::istream;
using std::setprecision;
using std::streamsize;
using std::cin;
using std::cout;
using std::endl;
using std::string;

// Organized / structured grade calculation program

// Call by value
double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}


// 4.1.1

// Bare vector<double> will copy the vector.  This is not the same as languages
// like Python or Java.  In Clojure, however, vectors are immutable anyway so
// the problem never arises.
double median(vector<double> vec) {
    // Type alias for vector size.
    typedef vector<double>::size_type vec_sz;
    
    vec_sz size = vec.size();
    if (size == 0)
        throw std::domain_error("cannot take the median of an empty vector");

    // Destructive sort, hence the pass by value
    sort(vec.begin(), vec.end());

    // Note that the use of the type vec_sz has remained local to this function,
    // which directly deals with vectors only.  This is a good way to constrain
    // the type.  Also note that it gets cast to double when returning.
    // And note that this is an implicit floor.
    vec_sz mid = size / 2;

    if  ((size % 2) == 0) {
        return (vec[mid] + vec[mid-1]) / 2;
    } else {
        return vec[mid];
    }
}

// 4.1.2

// Take the vector as a "reference to a vector of const doubles".
double grade(double midterm, double final, const vector<double>& hw) {
    // Note that here we check the condition of the function domain, even though
    // the median function will do so for us anyway.
    if (hw.size() == 0) {
        throw std::domain_error("student has done no homework");
    }

    // Delegate to the overloaded version which works on a simple double.
    // Not quite sure what happens here, I suppose that the vector will be copied
    // into the overloaded median.
    return grade(midterm, final, median(hw));
}

// 4.1.3

// We design this reading function to fill in the vector of the caller, then
// its return value can indicate success or failure.
// It's not that clear why not do it the other way, this is a bit of a C-ish
// way to do things IMO.

// A reference parameter without a const signals an intent to modify the 
// argument.  This changes the way you read code.

// K&M suggest clearing the caller's vector before reading, which seems like
// a pretty clear violation to me.
istream& read_hw(istream& in, vector<double>& hw) {
    // For some reason this doesn't work
    double x;

    while (in >> x)
        hw.push_back(x);

    // Clear any error condition on the stream, because we want to leave the
    // caller's stream in the same state as it was passed.
    in.clear();

    return in;
}

int main() {

    cout << "Please enter your first name:";
    string name;
    cin >> name;
    cout << "Hello, " << name << "!" << endl;

    cout << "Please enter your midterm and final exam grades: ";
    double midterm, final;
    
    cin >> midterm >> final;

    cout << "Enter all your homework grades, followed by eof: ";

    vector<double> homework;
    read_hw(cin, homework);

    try {
        // A subtle point is raised about the evaluation order here:
        // The implementation isn't required to evaluate the exprs in << 
        // from left to right.

        // Therefore, we must force the evaluation of grade() early, allowing
        // any exception to short-circuit the writing of "Final grade is:"
        // text.
        double final_grade = grade(midterm, final, homework);
        streamsize prec = cout.precision();

        cout << "Final grade is " << setprecision(3) << final_grade
             << setprecision(prec) << endl;

    } catch (std::domain_error&) {
        cout << endl << "You must enter your grades, try again" << endl;
        return 1;
    }

    return 0;
}
