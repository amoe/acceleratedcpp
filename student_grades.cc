#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using std::sort;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
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

    // Sort the homework grades
    // Pick the middle value
    // Determine if the size is odd or not
    // If the size is odd, we take floor(size / 2) as our middle val
    // If the size is even, we take (size/2) and ((size/2)+1) as our indices (which will
    // always be integral because size is even)
    // Pull them out, as value a and b, then result is (a+b)/2

    typedef vector<double>::size_type vec_sz;
    vec_sz size = homework_grades.size();

    if (size == 0) {
        cout << endl
             << "You didn't enter any grades, fool.  Terminating." 
             << endl;
        return 1;
    }

    // Otherwise we carry on.

    // Sort the grades using sort.

    sort(homework_grades.begin(), homework_grades.end());
    
    double median;

    if (size % 2 == 0) {
        // the size is even
        const vec_sz lower_mid = size / 2;
        const vec_sz upper_mid = lower_mid + 1;
        
        median =
            (homework_grades.at(lower_mid) + homework_grades.at(upper_mid))
            / 2;
    } else {
        const vec_sz mid = floor(size / 2.0);
        median = homework_grades.at(mid);
    }

    // Now write the result.
    streamsize previous_precision = cout.precision();
    cout << "Your final grade is "
         << setprecision(3)
         << median
         << setprecision(previous_precision)
         << endl;
}
