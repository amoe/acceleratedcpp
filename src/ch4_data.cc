#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

using std::istream;
using std::string;
using std::vector;
using std::sort;
using std::max;
using std::cin;
using std::cout;

struct StudentInfo {
    string name;
    double midterm, final;
    vector<double> homework;
};

istream& read_hw(istream& in, vector<double>& hw) {
    double x;

    while (in >> x)
        hw.push_back(x);

    in.clear();

    return in;
}

// read a single line of input into a StudentInfo object that the caller owns.
// we can reuse the previous function that we used to read the homework scores
istream& read(istream& is, StudentInfo& s) {
    is >> s.name >> s.midterm >> s.final;

    read_hw(is, s.homework);

    return is;
}

double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}


double median(vector<double> vec) {
    typedef vector<double>::size_type vec_sz;
    
    vec_sz size = vec.size();
    if (size == 0)
        throw std::domain_error("cannot take the median of an empty vector");

     sort(vec.begin(), vec.end());

     vec_sz mid = size / 2;

    if  ((size % 2) == 0) {
        return (vec[mid] + vec[mid-1]) / 2;
    } else {
        return vec[mid];
    }
}

// determine the grade of a student.  The const reference is just a performance
// thing.
double grade(const StudentInfo& s) {
    // Note that here we check the condition of the function domain, even though
    // the median function will do so for us anyway.
    if (s.homework.size() == 0) {
        throw std::domain_error("student has done no homework");
    }

    // Delegate to the overloaded version which works on a simple double.
    // Not quite sure what happens here, I suppose that the vector will be copied
    // into the overloaded median.
    return grade(s.midterm, s.final, median(s.homework));
}

// this will be used as a third argument to std::sort to compare studentinfo
// by grade, not sure about performance here... schwartzian transform?
// Actually we only need to do it by name, so ... yay
bool lessThan(const StudentInfo& x, const StudentInfo& y) {
    return x.name < y.name;
}

int main() {

    vector<StudentInfo> students;

    StudentInfo theRecord;

    // This *must* be size_type because both arguments to max() need to have
    // precisely the same type.  No idea why.
    string::size_type maxlen = 0;


    // Accumulate all students from cin
    while (read(cin, theRecord)) {
        maxlen = max(maxlen, theRecord.name.size());
        students.push_back(theRecord);
    }

    sort(students.begin(), students.end(), lessThan);

    for (vector<StudentInfo>::size_type i = 0; i < students.size(); i++) {
        StudentInfo thisStudent = students[i];
        cout << thisStudent.name
             << string((maxlen + 1) - thisStudent.name.size(), ' ');

        try {
            double finalGrade = grade(thisStudent);
            streamsize prec = cout.precision();

            cout << setprecision(3) << finalGrade << setprecision(prec);
        } catch (std::domain_error e) {
            cout << e.what();
        }
    }
    
}
