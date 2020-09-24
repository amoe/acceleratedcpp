#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "median.hh"
#include "read_hw.hh"
#include "grading_functions.hh"
#include "ch14_automatic.hh"

using std::setprecision;
using std::sort;
using std::max;
using std::min;
using std::istream;
using std::stringstream;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::runtime_error;
using std::domain_error;
using std::streamsize;

const string students_input = R"(
U Gamlin 94 89 14 96 16 63
U Capener 7 10 32 68 61 76
G Droney 31 75 83 81 54 18 87 
G Zutell 99 99 26 99 99 99 99 
)";

bool compare_Core_handles(
    const Handle<CoreStudent>& s1, const Handle<CoreStudent>& s2
) {
    return s1->name() < s2->name();
}

CoreStudent::CoreStudent(): midterm_grade(0), final_grade(0) {
}

CoreStudent::CoreStudent(istream& is) {
    read(is);
}

string CoreStudent::name() const {
    return n;
}

double CoreStudent::grade() const {
    return ::grade(midterm_grade, final_grade, homework);
}

istream& CoreStudent::read_common(istream& in) {
    in >> n >> midterm_grade >> final_grade;
    return in;
}

istream& CoreStudent::read(istream& in) {
    read_common(in);
    read_hw(in, homework);
    return in;
}

GradStudent::GradStudent(): thesis(0) {
}

GradStudent::GradStudent(istream& is) {
    read(is);
}

istream& GradStudent::read(istream& in) {
    CoreStudent::read_common(in);
    in >> thesis;
    read_hw(in, CoreStudent::homework);
    return in;
}

double GradStudent::grade() const {
    return min(CoreStudent::grade(), thesis);
}

template <typename T>
Handle<T>& Handle<T>::operator=(const Handle& rhs) {
    if (&rhs != this) {
        delete ptr;
        if (rhs.ptr) {
            ptr = rhs.ptr->clone();
        } else {
            ptr = 0;
        }
    }
    
    return *this;
}

template <typename T>
T& Handle<T>::operator*() const {
    if (ptr) {
        return *ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

template <typename T>
T* Handle<T>::operator->() const {
    if (ptr) {
        return ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

void dog_test() {
    Dog* dog = new Dog;
    
    Handle<Dog> handle1(dog);
    handle1->woof();

    cout << "Dog's val is " << (*handle1).val << endl;

    // Assignment should fully copy the Dog, using the synthetic copy
    // constructor created by the compiler.
    Handle<Dog> handle2;
    handle2 = handle1;
    handle2->val = 43;

    cout << "Handle1's val is " << (*handle1).val << endl;
    cout << "Handle2's val is " << (*handle2).val << endl;
}

void grading_test() {
    vector<Handle<CoreStudent>> students;
    Handle<CoreStudent> record;
    char ch;
    string::size_type maxlen = 0;
    stringstream sin(students_input);

    
    while (sin >> ch) {
        if (ch == 'U') {
            record = new CoreStudent;
        } else {
            record = new GradStudent;
        }

        record->read(sin);

        maxlen = max(maxlen, record->name().size());
        students.push_back(record);
    }

    cout << "Read " << students.size() << " students." << endl;

    sort(students.begin(), students.end(), compare_Core_handles);

    using vec_sz = vector<Handle<CoreStudent>>::size_type;

    
    for (vec_sz i = 0; i < students.size(); i++) {
        // Probably doing an unnecessary copy here.
        Handle<CoreStudent> s = students[i];
        cout << s->name()
             << string((maxlen + 1) - s->name().size(),  ' ');

        try {
            double final_grade = s->grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        } catch (domain_error& e) {
            cout << e.what() << endl;
        }
    }
}



int main() {
    cout << "Starting." << endl;

    dog_test();
    grading_test();
    
    cout << "End." << endl;
    return 0;
}
