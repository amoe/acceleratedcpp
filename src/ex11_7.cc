#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <numeric>
#include <algorithm>
#include "ex11_7.hh"

using std::sort;
using std::max;
using std::streamsize;
using std::setprecision;
using std::stringstream;
using std::domain_error;
using std::istream;
using std::cout;
using std::endl;
using std::string;

double median(Vec<double> vec) {
    typedef Vec<double>::size_type vec_sz;
    
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


istream& read_hw(istream& in, Vec<double>& hw);

class StudentInfo {
public:
    StudentInfo();
    StudentInfo(istream&);

    double grade() const;
    istream& read(istream&);
    string name() const {
        return n;
    }

    bool valid() const {
        return homework.size() != 0;
    }

private:
    Vec<double> homework;
    string n;
    double midterm, final;
};

StudentInfo::StudentInfo(): midterm(0), final(0) {
}

StudentInfo::StudentInfo(istream& is) {
    read(is);
}

double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const Vec<double>& hw) {
    if (hw.size() == 0) {
        throw domain_error("student has done no homework");
    }

    return grade(midterm, final, median(hw));
}

double StudentInfo::grade() const {
    return ::grade(midterm, final, homework);
}

istream& StudentInfo::read(istream& in) {
    in >> n >> midterm >> final;
    read_hw(in, homework);
    return in;
}

istream& read_hw(istream& in, Vec<double>& hw) {
    if (in) {
        double x;
        while (in >> x)
            hw.push_back(x);

        in.clear();
    }

    return in;
}

bool compare(const StudentInfo& x, const StudentInfo& y) {
    return x.name() < y.name();
}

const string multi_line_input = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";


void do_ch9_programs() {
    Vec<StudentInfo> students;
    StudentInfo the_record;
    string::size_type maxlen = 0;

    stringstream sin1(multi_line_input);

    

    while (the_record.read(sin1)) {
        maxlen = max(maxlen, the_record.name().size());
         students.push_back(the_record);
    }


    sort(students.begin(), students.end(), compare);

    for (Vec<StudentInfo>::size_type i = 0; i < students.size(); i++) {
        StudentInfo this_student = students[i];
        cout << this_student.name()
             << string((maxlen + 1) - this_student.name().size(), ' ');

        try {
            if (!this_student.valid()) {
                cout << "skipping invalid student" << endl;
            }

            double final_grade = this_student.grade();
            streamsize prec = cout.precision();

            cout << setprecision(3) << final_grade << setprecision(prec);
        } catch (std::domain_error& e) {
            cout << e.what();
        }

        cout << endl;
    }
}

string::size_type width(const Vec<string>& v) {
    string::size_type maxlen = 0;

    for (Vec<string>::size_type i = 0; i < v.size(); i++) {
        maxlen = max(maxlen, v[i].size());
    }

    return maxlen;
}

Vec<string> frame(const Vec<string>& words) {
    Vec<string> result;
    string::size_type maxlen = width(words);
    string border(maxlen + 4, '*');

    result.push_back(border);

    for (Vec<string>::size_type i = 0; i < words.size(); i++) {
        string padding(maxlen - words[i].size(), ' ');
        
        result.push_back("* "  + words[i] + padding + " *");
    }

    result.push_back(border);

    return result;
}

Vec<string> vcat(const Vec<string>& top, const Vec<string>& bottom) {
    Vec<string> result = top;

    for (
        Vec<string>::const_iterator iter = bottom.begin();
        iter != bottom.end();
        iter++
    ) {
        result.push_back(*iter);
    }

    return result;
}


Vec<string> hcat(const Vec<string>& left, const Vec<string>& right) {
    Vec<string> result;

    string::size_type widthLeft = width(left) + 1;
    Vec<string>::size_type i = 0, j = 0;

    while (i != left.size() || j != right.size()) {
        string s;

        if (i != left.size()) {
            s = left[i];
            i++;
        }

        s += string(widthLeft - s.size(), ' ');

        if (j != right.size()) {
            s += right[j];
            j++;
        }

        
        result.push_back(s);
    }

    return result;
}



void spew(const Vec<string>& pic) {
    for (auto line : pic) {
        std::cout << line << std::endl;
    }
}

void do_ch5_programs() {
    Vec<string> result;
    // We don't have a way to accept a static initializer list like a real
    // vector can.
    result.push_back("The");
    result.push_back("quick");
    result.push_back("brown");
    result.push_back("fox");
    result.push_back("jumped");
    result.push_back("over");
    result.push_back("the");
    result.push_back("lazy");
    result.push_back("dog");

    Vec<string> framed = frame(result);
    spew(framed);

    spew(vcat(result, framed));
    spew(hcat(result, framed));
}

int main() {
    cout << "Starting." << endl;

    do_ch9_programs();
    do_ch5_programs();

    cout << "End." << endl;
    return 0;
}
