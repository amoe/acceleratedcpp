#ifndef CH14_AUTOMATIC_HH
#define CH14_AUTOMATIC_HH

class Dog {
public:
    Dog(): val(42) { }

    Dog* clone() {
        return new Dog(*this);
    }
    
    void woof() {
        std::cout << "Woof!  woof!" << std::endl;
    }

    int val;
};

template <typename T>
class Handle {
public:
    Handle(): ptr(0) { }
    Handle(const Handle& source): ptr(0) {
        if (source.ptr) {
            ptr = source.ptr->clone();
        }
    }
    Handle& operator=(const Handle&);
    ~Handle() {
        delete ptr;
    }
    
    Handle(T* ptr): ptr(ptr) { }
    
    operator bool() const {
        return ptr;    // 0 if null, and hence false
    }
    
    T& operator*() const;
    T* operator->() const;
    
private:
    T* ptr;
};

template <typename T>
class RefHandle {
public:
    RefHandle(): ptr(0), refptr(new size_t(1)) {
    }
    
    
    RefHandle(T* ptr): ptr(ptr), refptr(new size_t(1)) { }
    RefHandle(const RefHandle& source);
    RefHandle& operator=(const RefHandle&);
    ~RefHandle();
    
    operator bool() const {
        return ptr;    // 0 if null, and hence false
    }
    
    T& operator*() const;
    T* operator->() const;

    void print_identity() const {
        std::cout << ptr << std::endl;
    }

    size_t get_refcount() const {
        return *refptr;
    }
    
private:
    T* ptr;
    size_t* refptr;
};


// XXX: ???  Used within make_unique().
template <typename T>
T* clone(const T* tp) {
    return tp->clone();
}

// A template specialization:
// Basically an override for a more general template.  When clone() gets called
// with T=vector<char>, we substitute this definition for the one that directly
// calls clone().
template <>
vector<char>* clone(const vector<char>* vec) {
    return new vector<char>(*vec);
}

// Called Ptr by K&M but ControllableHandle captures what it does better: allows
// deferring copying decisions to user-code.  "LateBindingHandle", perhaps.
// It acts like a RefHandle until the user calls make_unique(), at which point
// it acts like a Handle.
// make_unique() might also have been named 'detach()', because it effectively
// detaches the object from its reference count pool.
template <typename T>
class ControllableHandle {
public:
    void make_unique() {
        // If it's alive, the value of *refptr can never be zero,
        // so the condition is equivalent to *refptr > 1.
        if (*refptr != 1) {
            --*refptr;    // This object has been detached.
            refptr = new size_t(1);   // It forms a new pool.
            ptr = ptr ? clone(ptr) : 0;
        }
    }
    
    ControllableHandle(): ptr(0), refptr(new size_t(1)) {
    }
    
    
    ControllableHandle(T* ptr): ptr(ptr), refptr(new size_t(1)) { }

    ControllableHandle(const ControllableHandle& source): ptr(source.ptr), refptr(source.refptr) {
        *refptr++;
    }

    ControllableHandle& operator=(const ControllableHandle&);
    ~ControllableHandle();
    
    operator bool() const {
        return ptr;    // 0 if null, and hence false
    }
    
    T& operator*() const;
    T* operator->() const;
    
private:
    T* ptr;
    size_t* refptr;
};


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


private:
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

class StudentInfo1 {
public:
    StudentInfo1() { }

    StudentInfo1(std::istream& is) { read(is); }

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

    static bool compare(const StudentInfo1& s1, const StudentInfo1& s2) {
        return s1.name() < s2.name();
    }

private:
    Handle<CoreStudent> cp;
};

class StudentInfo2 {
public:
    StudentInfo2() { }
    StudentInfo2(std::istream& is) { read(is); }

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

    static bool compare(const StudentInfo2& s1, const StudentInfo2& s2) {
        return s1.name() < s2.name();
    }

    void print_identity() const {
        cp.print_identity();
    }

    int get_refcount() const {
        return cp.get_refcount();
    }

private:
    RefHandle<CoreStudent> cp;
};

#endif /* CH14_AUTOMATIC_HH */
