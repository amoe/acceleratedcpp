#ifndef EX13_5_HH
#define EX13_5_HH

class CoreStudent {
public:
    CoreStudent();
    CoreStudent(std::istream&);
    std::string name() const;
    virtual std::istream& read(std::istream&);
    virtual double grade() const;
    virtual ~CoreStudent() { }

    operator bool() const;
    
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


private:
    std::string n;
};

class GradStudent: public CoreStudent {
public:
    GradStudent();
    GradStudent(std::istream&);
    double grade() const;
    std::istream& read(std::istream&);
    GradStudent* clone() const {
        return new GradStudent(*this);
    }
    void regrade(double d1, double d2) {
        final_grade = d1;
        thesis = d2;
    }
    operator bool() const;

private:
    double thesis;
};



#endif /* EX13_5_HH */

