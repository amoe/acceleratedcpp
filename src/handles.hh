#ifndef HANDLES_HH
#define HANDLES_HH

#include <iostream>
#include <cstddef>

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
        return ptr;
    }
    
    T& operator*() const;
    T* operator->() const;
    
private:
    T* ptr;
};

template <typename T>
class RefHandle {
public:
    RefHandle(): ptr(0), refptr(new std::size_t(1)) {
    }
    
    
    RefHandle(T* ptr): ptr(ptr), refptr(new std::size_t(1)) { }
    RefHandle(const RefHandle& source);
    RefHandle& operator=(const RefHandle&);
    ~RefHandle();
    
    operator bool() const {
        return ptr;
    }
    
    T& operator*() const;
    T* operator->() const;

    void print_identity() const {
        std::cout << ptr << std::endl;
    }

    std::size_t get_refcount() const {
        return *refptr;
    }
    
private:
    T* ptr;
    std::size_t* refptr;
};

template <typename T>
class ControllableHandle {
public:
    void make_unique() {
        if (*refptr != 1) {
            --*refptr;
            refptr = new std::size_t(1);
            ptr = ptr ? clone(ptr) : 0;
        }
    }
    
    ControllableHandle(): ptr(0), refptr(new std::size_t(1)) {
    }
    
    
    ControllableHandle(T* ptr): ptr(ptr), refptr(new std::size_t(1)) { }

    ControllableHandle(const ControllableHandle& source): ptr(source.ptr), refptr(source.refptr) {
        (*refptr)++;
    }

    ControllableHandle& operator=(const ControllableHandle&);
    ~ControllableHandle();
    
    operator bool() const {
        return ptr;
    }
    
    T& operator*() const;
    T* operator->() const;

    int get_refcount() const {
        return *refptr;
    }
    
private:
    T* ptr;
    std::size_t* refptr;
};



#endif /* HANDLES_HH */

