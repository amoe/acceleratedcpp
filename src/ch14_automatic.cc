#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include "median.hh"
#include "read_hw.hh"
#include "grading_functions.hh"
#include "ch14_automatic.hh"

using std::vector;
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

const string corestudents_only = R"(
Gamlin 94 89 14 96 16 63
Capener 7 10 32 68 61 76
)";

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

template <typename T>
T& RefHandle<T>::operator*() const {
    if (ptr) {
        return *ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

template <typename T>
T* RefHandle<T>::operator->() const {
    if (ptr) {
        return ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

template <typename T>
RefHandle<T>::~RefHandle() {
    (*refptr)--;
    if (refptr == 0) {
        delete refptr;
        delete ptr;
    }
}


// Copying increments the count which is shared between the instances.  ONLY
// copying does this.  Creating new RefHandles via the constructor RefHandle(T*)
// will just construct a totally new instance, which may destroy the object too
// soon.
template <typename T>
RefHandle<T>::RefHandle(const RefHandle& source): ptr(source.ptr), refptr(source.refptr) {
    ++*refptr;   // order prevents some need for parens, still means (*refptr)++
}


template <typename T>
RefHandle<T>& RefHandle<T>::operator=(const RefHandle& rhs) {
    // Very obscure:
    // This protects against self-assignment, because if it's the same object,
    // it gets its count incremented and then decremented meaning it stays static,
    // and therefore won't be destroyed in the following call.
    // As it needed to be incremented anyway, doing it here kills two birds with
    // one stone, so to speak.
    // This is quite tricky code.
    ++*(rhs.refptr);

    // Because we have been assigned to, we may need to delete our contents
    if (--*refptr == 0) {
        delete refptr;
        delete ptr;
    }

    refptr = rhs.refptr;   // No modifications needed here -- already done above.
    ptr = rhs.ptr;
    return *this;
}

template <typename T>
T& ControllableHandle<T>::operator*() const {
    if (ptr) {
        return *ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

template <typename T>
T* ControllableHandle<T>::operator->() const {
    if (ptr) {
        return ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

template <typename T>
ControllableHandle<T>::~ControllableHandle() {
    if (--*refptr == 0) {
        delete refptr;
        delete ptr;
    }
}

// See notes for RefHandle
template <typename T>
ControllableHandle<T>& ControllableHandle<T>::operator=(const ControllableHandle& rhs) {
    ++*(rhs.refptr);

    if (--*refptr == 0) {
        delete refptr;
        delete ptr;
    }

    refptr = rhs.refptr;
    ptr = rhs.ptr;
    return *this;
}


// Code looks the same, but the Handle constructor is implicitly called!
istream& StudentInfo1::read(istream& is) {
    char ch;
    is >> ch;

    if (ch == 'U') {
        cp = new CoreStudent(is);
    } else {
        cp = new GradStudent(is);
    }

    return is;
}

istream& StudentInfo2::read(istream& is) {
    char ch;
    is >> ch;

    // Call RefHandle assignment operator here.
    // The compiler will also IMPLICITLY CALL THE REFHANDLE DESTRUCTOR.
    // However this doesn't even matter in this case because the assignment
    // operator automatically frees the left-hand-side.
    if (ch == 'U') {
        cp = new CoreStudent(is);
    } else {
        cp = new GradStudent(is);
    }
    return is;
}

void dog_handle_test() {
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

void dog_refhandle_test() {
    Dog* dog = new Dog;
    
    RefHandle<Dog> handle1(dog);
    handle1->woof();

    cout << "Dog's val is " << (*handle1).val << endl;

    RefHandle<Dog> handle2;
    handle2 = handle1;
    handle2->val = 43;

    cout << "Handle1's val is " << (*handle1).val << endl;
    cout << "Handle2's val is " << (*handle2).val << endl;
}

void dog_controllablehandle_test() {
    Dog* dog = new Dog;
    
    ControllableHandle<Dog> handle1(dog);
    handle1->woof();

    cout << "Dog's val is " << (*handle1).val << endl;

    ControllableHandle<Dog> handle2;
    handle2 = handle1;
    handle2->val = 43;

    cout << "Handle1's val is " << (*handle1).val << endl;
    cout << "Handle2's val is " << (*handle2).val << endl;
}

void grading_test_with_direct_handle() {
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

void grading_test_with_studentinfo1() {
    vector<StudentInfo1> students;
    StudentInfo1 record;
    char ch;
    string::size_type maxlen = 0;
    stringstream sin(students_input);

    while (record.read(sin)) {
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    cout << "Read " << students.size() << " students." << endl;

    sort(students.begin(), students.end(), StudentInfo1::compare);
    using vec_sz = vector<StudentInfo1>::size_type;

    
    for (vec_sz i = 0; i < students.size(); i++) {
        // Probably doing an unnecessary copy here.
        StudentInfo1 s = students[i];
        cout << s.name()
             << string((maxlen + 1) - s.name().size(),  ' ');

        try {
            double final_grade = s.grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        } catch (domain_error& e) {
            cout << e.what() << endl;
        }
    }
}

// It's not 100% clear that this works correctly.
void grading_test_with_studentinfo2() {
    vector<StudentInfo2> students;
    StudentInfo2 record;
    char ch;
    string::size_type maxlen = 0;
    stringstream sin(students_input);


    while (record.read(sin)) {
        cout << "Content of record: '" << record.name() << "'" << endl;
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    cout << "Read " << students.size() << " students." << endl;

    sort(students.begin(), students.end(), StudentInfo2::compare);
    using vec_sz = vector<StudentInfo2>::size_type;

    
    for (vec_sz i = 0; i < students.size(); i++) {
        // Probably doing an unnecessary copy here.
        StudentInfo2& s = students[i];
        cout << s.name() << "(" << s.get_refcount() << ")"
             << string((maxlen + 1) - s.name().size(),  ' ');

        try {
            double final_grade = s.grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        } catch (domain_error& e) {
            cout << e.what() << endl;
        }
    }
}


void handle_copies_test() {
    // Demonstrate that use of Handle causes object aliases to not affect each
    // other.  read() is the only way that we can modify objects through
    // StudentInfo at present.
    stringstream sin(students_input);
    StudentInfo1 s1(sin);
    cout << "Student grade of s1 is " << s1.grade() << endl;
    StudentInfo1 s2 = s1;
    s2.read(sin);
    cout << "Student grade of s2 is " << s2.grade() << endl;
    cout << "Student grade of s1 is still " << s1.grade() << endl;
}

void refhandle_overwrites_test1() {
    stringstream sin(corestudents_only);
    RefHandle<CoreStudent> record(new CoreStudent);
    record->read(sin);
    cout << "Student grade is firstly " << record->grade() << endl;

    RefHandle<CoreStudent> record2(record);
    record2->read(sin);
    cout << "Student grade is secondly " << record->grade() << endl;
}

// Demonstrating the assignment operator reference beha
void refhandle_overwrites_test2() {
    stringstream sin(students_input);
    StudentInfo2 s1(sin);   // Calls RefHandle assignment operator
    
    cout << "s1's grade is " << s1.grade() << endl;
    StudentInfo2 s2 = s1;
    s2 = s1;
    s2.read(sin);

    cout << "s1's grade is now " << s1.grade() << endl;
}

// Created to answer the question: why do we only have 1 reference at the end,
// rather than two, when the StudentInfo2 'record' is still in scope?

// The answer is that the final 'read()' causes a blank StudentInfo2 to be
// stored in 'record', but that blank StudentInfo2 never reaches the vector due
// to the structure of the 'while' condition.
void refhandle_reference_count_test3() { 
    vector<StudentInfo2> students;
    StudentInfo2 record;
    char ch;
    stringstream sin(students_input);

    while (record.read(sin)) {
        cout << "Content of record: '" << record.name() << "'" << endl;
        cout << record.get_refcount() << endl;
        // Should increment the ref count.
        cout << "About to push" << endl;
        students.push_back(record);
        cout << "Finished pushing" << endl;
    }

    cout << "Read " << students.size() << " students." << endl;

    using vec_sz = vector<StudentInfo2>::size_type;
    
    for (vec_sz i = 0; i < students.size(); i++) {
        // Reference to avoid accidentally incrementing the refcount.
        StudentInfo2& s = students[i];
        cout << s.name() << "(" << s.get_refcount() << ")" << endl;
    }
}

void str_test() {
    Str name = "Dave";
    Str greeting = "Hello, " + name + "!";
    cout << "Greeting is now: '" + greeting + "'" << endl;
}

void str_test_compound_concatenation() {
    Str name1 = "Dave";
    cout << "Refcount is " << name1.get_refcount() << endl;
    Str name2 = name1;    // Should not copy.
    cout << "Refcount is " << name1.get_refcount() << endl;

    name1 += " Lister";
    cout << "Name1 is now '" << name1 << "'" << endl;
    cout << "Name2 is now '" << name2 << "'" << endl;

    cout << "Refcount of name1 is " << name1.get_refcount() << endl;
    cout << "Refcount of name2 is " << name2.get_refcount() << endl;
}

void str_test_lvalue_subscript() {
    Str name1 = "Dave";
    Str name2 = name1;

    name1[1] = 'i';

    cout << "Name1 is now: '" << name1 << "'" << endl;
    cout << "Name2 is now: '" << name2 << "'" << endl;
}

void str_test_input() {
    Str s1("Dave");
    Str s2 = s1;
    stringstream ss_val(" Lister");
    ss_val >> s1;

    cout << "s1 is now " << s1 << endl;
    cout << "s2 is now " << s2 << endl;
}

int main() {
    cout << "Starting." << endl;

    dog_handle_test();
    dog_refhandle_test();
    dog_controllablehandle_test();

    handle_copies_test();

    refhandle_overwrites_test1();
    refhandle_overwrites_test2();
    refhandle_reference_count_test3();

    cout << "Direct use of Handle:" << endl;
    grading_test_with_direct_handle();

    cout << "Use of StudentInfo1 (indirectly using Handle):" << endl;
    grading_test_with_studentinfo1();

    cout << "Use of StudentInfo2 (using RefHandle):" << endl;
    grading_test_with_studentinfo2();

    cout << "Str memory handling tests:" << endl;
    
    str_test();
    str_test_compound_concatenation();
    str_test_lvalue_subscript();
    str_test_input();
    
    cout << "End." << endl;
    return 0;
}
