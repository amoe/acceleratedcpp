#ifndef EX14_6_HH
#define EX14_6_HH

class ReferenceCounter {
public:
    ReferenceCounter(): refptr(new std::size_t(1)) {
    }

    ReferenceCounter(const ReferenceCounter& source): refptr(source.refptr) {
    }
    
    
    ~ReferenceCounter() {
        if (is_dead()) {
            delete refptr;
        }
    }
    ReferenceCounter& operator=(const ReferenceCounter& source) {
        if (&source != this) {
            delete refptr;
            refptr = source.refptr;
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
        (*refptr)--;
    }
    
    int get_refcount() const {
        return *refptr;
    }

    void print_identity() const {
        std::cout << "counter identity is: " << refptr << std::endl;
    }

private:
    std::size_t* refptr;
};

template <typename T>
class ControllableHandle2 {
public:
    ControllableHandle2(): ptr(0) {
    }
    
    ControllableHandle2(T* ptr): ptr(ptr) {
    }

    ControllableHandle2(
        const ControllableHandle2& source
    ): ptr(source.ptr), counter(source.counter) {
        counter.increment();
    }

    ~ControllableHandle2() {
        counter.decrement();
        if (counter.is_dead()) {
            delete ptr;
        } else {
        }
    }

    ControllableHandle2& operator=(ControllableHandle2& rhs) {
        rhs.counter.increment();
        counter.decrement();

        if (counter.is_dead()) {
            delete ptr;
        }

        counter = rhs.counter;
        ptr = rhs.ptr;
        return *this;
    }

    int get_refcount() const {
        return counter.get_refcount();
    }
    
private:
    T* ptr;
    ReferenceCounter counter;  //??? pointer?
};

#endif /* EX14_6_HH */
