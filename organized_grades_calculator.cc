#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

using std::vector;
using std::sort;

// Organized / structured grade calculation program

// Call by value
double grade(double midterm, double final, double homework) {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}


// 4.1.1

// Bare vector<double> will copy the vector.  This is not the same as languages
// like Python or Java.  In Clojure, however, vectors are immutable anyway so
// the problem never arises.
double median(vector<double> vec) {
    // Type alias for vector size.
    typedef vector<double>::size_type vec_sz;
    
    vec_sz size = vec.size();
    if (size == 0)
        throw std::domain_error("cannot take the median of an empty vector");

    // Destructive sort, hence the pass by value
    sort(vec.begin(), vec.end());

    // Note that the use of the type vec_sz has remained local to this function,
    // which directly deals with vectors only.  This is a good way to constrain
    // the type.  Also note that it gets cast to double when returning.
    // And note that this is an implicit floor.
    vec_sz mid = size / 2;

    if  ((size % 2) == 0) {
        return (vec[mid] + vec[mid-1]) / 2;
    } else {
        return vec[mid];
    }
}

// 4.1.2

// Take the vector as a "reference to a vector of const doubles".
double grade(double midterm, double final, const vector<double>& hw) {
    // Note that here we check the condition of the function domain, even though
    // the median function will do so for us anyway.
    if (hw.size() == 0) {
        throw std::domain_error("student has done no homework");
    }

    // Delegate to the overloaded version which works on a simple double.
    // Not quite sure what happens here, I suppose that the vector will be copied
    // into the overloaded median.
    return grade(midterm, final, median(hw));
}

int main() { }
