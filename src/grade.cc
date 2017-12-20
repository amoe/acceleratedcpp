#include <stdexcept>
#include "student_info.hh"
#include "median.hh"
#include "grade.hh"

double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
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

