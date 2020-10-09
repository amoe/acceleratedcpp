#ifndef EX14_6_HH
#define EX14_6_HH

class ReferenceCounter {
public:
    ReferenceCounter(): refptr(new std::size_t(1)) {
    }

    bool is_sole_referent() {
        return *refptr == 1;
    }

    bool is_dead() {
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

private:
    std::size_t* refptr;
};

#endif /* EX14_6_HH */
