#include <string>
#include <vector>

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
