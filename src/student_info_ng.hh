#ifndef STUDENT_INFO_NG_HH
#define STUDENT_INFO_NG_HH

class StudentInfo {
public:
    StudentInfo(): student(0) { }
    
    StudentInfo(std::istream& is): student(0) {
        read(is);
    }

    std::istream& read(std::istream& is);

    StudentInfo& operator=(const StudentInfo& source) {
        if (&source != this) {
            delete student;
            if (source.student) {
                student = source.student->clone();
            } else{
                student = 0;
            }
        }

        return *this;
    }

    StudentInfo(const StudentInfo& source) {
        // Polymorphically call through to the clone function.
        if (source.student) 
            student = source.student->clone();
    }
    
    
    double grade() const {
        return student->grade();
    }
    
    std::string name() const {
        return student->name();
    }

    ~StudentInfo() {
        delete student;
    }

    static bool compare(const StudentInfo& s1, const StudentInfo& s2) {
        return s1.name() < s2.name();
    }
    
private:
    CoreStudent* student;
};

#endif /* STUDENT_INFO_NG_HH */
