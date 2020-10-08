#ifndef EX14_3_HH
#define EX14_3_HH

class StudentInfo {
public:
    StudentInfo() { }
    StudentInfo(std::istream& is) { read(is); }

    std::istream& read(std::istream&);

    std::string name() const {
        if (cp) {
            return cp->name();
        } else {
            throw std::runtime_error("uninitialized Student");
        }
    }

    double grade() const {
        if (cp) {
            return cp->grade();
        } else {
            throw std::runtime_error("uninitialized Student");
        }
    }

    static bool compare(const StudentInfo& s1, const StudentInfo& s2) {
        return s1.name() < s2.name();
    }

    void print_identity() const {
        cp.print_identity();
    }

    int get_refcount() const {
        return cp.get_refcount();
    }

private:
    ControllableHandle<CoreStudent> cp;
};

#endif /* EX14_3_HH */
