#ifndef GRADING_FUNCTIONS_HH
#define GRADING_FUNCTIONS_HH

#include <vector>

double grade(double midterm, double final, double homework);
double grade(double midterm, double final, const std::vector<double>& hw);

#endif /* GRADING_FUNCTIONS_HH */


