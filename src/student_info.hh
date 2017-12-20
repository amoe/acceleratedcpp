#ifndef STUDENT_INFO_HH
#define STUDENT_INFO_HH

#include <string>
#include <vector>

struct StudentInfo {
    std::string name;
    double midterm, final;
    std::vector<double> homework;
};

bool lessThan(const StudentInfo&, const StudentInfo&);
std::istream& read(std::istream&, StudentInfo&);
std::istream& read_hw(std::istream&, std::vector<double>&);

#endif // STUDENT_INFO_HH
