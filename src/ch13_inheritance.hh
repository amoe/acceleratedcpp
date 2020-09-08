#ifndef CH13_INHERITANCE_HH
#define CH13_INHERITANCE_HH

class CoreStudent {
public:
    CoreStudent();
    CoreStudent(std::istream&);
    std::string name() const;
    virtual std::istream& read(std::istream&);
    virtual double grade() const;
    virtual ~CoreStudent() { }
    
protected:
    std::istream& read_common(std::istream&);
    double midterm_grade, final_grade;
    std::vector<double> homework;

private:
    std::string n;
};

class GradStudent: public CoreStudent {
public:
    GradStudent();
    GradStudent(std::istream&);
    double grade() const;    // Note that we re-declare methods we will override
    std::istream& read(std::istream&);

private:
    double thesis;
};

class StudentInfo {
public:
    StudentInfo(char type_code, istream& is) {
        if (type_code == 'U') {
            student = new CoreStudent(is);
        } else {
            student = new GradStudent(is);
        }
    }

    StudentInfo& operator=(const StudentInfo& source) {
        student = source.student;
        return *this;
    }

    StudentInfo(const StudentInfo& source) {
        // no idea how to copy this correctly without storing type code on the
        // object
//        student = new source.student;
    }
    
    
    
    double grade() const {
        return student->grade();
    }
    
    std::string name() {
        return student->name();
    }

    ~StudentInfo() {
        delete student;
    }
    
private:
    CoreStudent* student;
};


#endif /* CH13_INHERITANCE_HH */
