#ifndef EX13_6_HH
#define EX13_6_HH

class CoreStudent {
public:
    CoreStudent();
    CoreStudent(std::istream&);
    std::string name() const;
    virtual std::istream& read(std::istream&);
    virtual double grade() const;
    virtual ~CoreStudent() { }
    void regrade(double d) {
        final_grade = d;
    }
    
protected:
    std::istream& read_common(std::istream&);
    double midterm_grade, final_grade;
    std::vector<double> homework;
    std::string n;
};

class AuditStudent: public CoreStudent {
public:
    AuditStudent(std::istream&);
    std::istream& read(std::istream&);
    double grade() const;
};

#endif /* EX13_1_HH */

