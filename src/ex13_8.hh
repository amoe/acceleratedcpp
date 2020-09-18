#ifndef EX13_8_HH
#define EX13_8_HH

class CoreStudent {
public:
    CoreStudent();
    CoreStudent(std::istream&);
    std::string name() const;
    virtual std::istream& read(std::istream&);
    virtual double grade() const;
    virtual ~CoreStudent() { }
    virtual CoreStudent* clone() const {
        return new CoreStudent(*this);
    }
    void regrade(double d) {
        final_grade = d;
    }
    
protected:
    std::istream& read_common(std::istream&);
    double midterm_grade, final_grade;
    std::vector<double> homework;
    std::string n;
};

class GradStudent: public CoreStudent {
public:
    GradStudent();
    GradStudent(std::istream&);
    double grade() const;    // Note that we re-declare methods we will override
    std::istream& read(std::istream&);
    GradStudent* clone() const {
        return new GradStudent(*this);
    }
    void regrade(double d1, double d2) {
        final_grade = d1;
        thesis = d2;
    }

private:
    double thesis;
};

class AuditStudent: public CoreStudent {
public:
    AuditStudent(std::istream&);
    std::istream& read(std::istream&);
    double grade() const;

    // Needed in every derived class, because copying will otherwise cause the
    // pointer to degrade to a CoreStudent, which means its overrides won't get
    // called after it's been pushed onto a vector.
    AuditStudent* clone() const {
        return new AuditStudent(*this);
    }
};

class PassFailStudent: public CoreStudent {
public:
    PassFailStudent(std::istream&);
    double grade() const;
    PassFailStudent* clone() const {
        return new PassFailStudent(*this);
    }
};


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


#endif /* EX13_8_HH */
