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

    int count = 0;
    double sum = 0;
    double thisGrade;

    // Invariant:
    // 2 clauses:
    //   * we have read `count` grades so far, and
    //   *  `sum` is the sum of the grades that we have read
    //
    // I suppose that cin returns 0 or NULL on EOF.
    while (cin >> thisGrade) {
        ++count;             // after this the second clause of the invariant is false
        sum += thisGrade;    // after this they both become true
    }

    // Now write the result.
    streamsize previous_precision = cout.precision();
    cout << "Your final grade is "
         << setprecision(3)
         << 0.2 * midterm_grade + 0.4 * final_grade + 0.4 * sum / count
         << setprecision(previous_precision)
         << endl;

}
