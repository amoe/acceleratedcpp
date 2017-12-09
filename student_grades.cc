#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

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

    // I suppose that cin returns 0 or NULL on EOF.
    while (cin >> thisGrade) {
        ++count;
        sum += thisGrade;
    }
}
