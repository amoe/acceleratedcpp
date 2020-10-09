#ifndef EX14_6_HH
#define EX14_6_HH

// XXX destructor for the size_t?
class ReferenceCounter {
public:
    ReferenceCounter(): refptr(new std::size_t(1)) {
    }

    ReferenceCounter(const ReferenceCounter& source): refptr(source.refptr) { }
    ~ReferenceCounter() {
        if (is_dead()) {
            delete refptr;
        }
    }
    ReferenceCounter& operator=(const ReferenceCounter& source) {
        if (&source != this) {
            delete refptr;
            refptr = new std::size_t(*source.refptr);   // ??? this is a real value copy
            // not really sure that's what we want?  but we don't ever use this function
        }
        
        return *this;
    }

    bool is_sole_referent() const {
        return *refptr == 1;
    }

    bool is_dead() const {
        return *refptr == 0;
    }
    
    void increment() {
        (*refptr)++;
    }

    void decrement() {
        std::cout << "inside decrement method" << std::endl;
        (*refptr)--;
    }
    
    int get_refcount() const {
        return *refptr;
    }

private:
    std::size_t* refptr;
};

template <typename T>
class ControllableHandle2 {
public:
    ControllableHandle2(T* ptr): ptr(ptr) {
    }

    ControllableHandle2(
        const ControllableHandle2& source
    ): ptr(source.ptr), counter(source.counter) {
        std::cout << "ControllableHandle2: inside copy constructor" << std::endl;
        counter.increment();
    }

    ~ControllableHandle2() {
        std::cout << "ControllableHandle2: inside destructor for " << this << std::endl;
        std::cout << "ref count pre decrement is " << counter.get_refcount() << std::endl;
        counter.decrement();

        std::cout << "ref count is " << counter.get_refcount() << std::endl;
        
        if (counter.is_dead()) {
            std::cout << "about to delete" << std::endl;
            delete ptr;
        } else {
            std::cout << "preserving because of live references" << std::endl;
        }
    }

    ControllableHandle2& operator=(ControllableHandle2& rhs) {
        std::cout << "ControllableHandle2: inside assignment operator" << std::endl;
        
        rhs.counter.increment();
        rhs.counter.decrement();

        if (rhs.counter.is_dead()) {
            delete ptr;
        }

        counter = rhs.counter;
        ptr = rhs.ptr;
    }

    int get_refcount() const {
        return counter.get_refcount();
    }
    
private:
    T* ptr;
    ReferenceCounter counter;  //??? pointer?
};

#endif /* EX14_6_HH */
