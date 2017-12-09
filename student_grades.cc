#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

using std::streamsize;
using std::setprecision;


int main() {

    cout << "Please enter your first name: ";
    string name;
    cin >> name;

    cout << "Hello, " << name << "!" << endl;


    cout << "Please enter your midterm and final exam grades (separated by spaces): ";
    double midterm_grade;
    double final_grade;

    // I suppose that this syntax repeatedly reads because (cin >> x) yields cin.
    cin >> midterm_grade >> final_grade;

    // This uses the string pasting feature of the preprocessor.
    cout << "Enter all your homework grades, "
        "followed by end-of-file: ";

    double this_grade;
    vector<double> homework_grades;

    // loop invariant: homework_grades contains all grades read so far
    // I suppose that cin returns 0 or NULL on EOF.
    while (cin >> this_grade) {
        homework_grades.push_back(this_grade);
    }

    // Now compute the median.

    double median_grade;

    // Now write the result.
    streamsize previous_precision = cout.precision();
    cout << "Your final grade is "
         << setprecision(3)
         << median_grade
         << setprecision(previous_precision)
         << endl;
}
