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


#endif /* CH14_AUTOMATIC_HH */
