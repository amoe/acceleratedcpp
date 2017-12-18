#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using std::istream;
using std::string;
using std::vector;
using std::sort;

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

// determine the grade of a student
double grade(const StudentInfo& s) 
{
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

int main() {
}
