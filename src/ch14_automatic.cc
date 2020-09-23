#include <iostream>
#include <stdexcept>
#include "ch14_automatic.hh"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename T>
Handle<T>& Handle<T>::operator=(const Handle& rhs) {
    if (&rhs != this) {
        delete ptr;
        if (rhs.ptr) {
            ptr = rhs.ptr->clone();
        } else {
            ptr = 0;
        }
    }
    
    return *this;
}

template <typename T>
T& Handle<T>::operator*() const {
    if (ptr) {
        return *ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

template <typename T>
T* Handle<T>::operator->() const {
    if (ptr) {
        return ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

int main() {
    cout << "Starting." << endl;

    Dog* dog = new Dog;
    
    Handle<Dog> handle1(dog);
    handle1->woof();

    cout << "Dog's val is " << (*handle1).val << endl;

    
    // Assignment should fully copy the Dog, using the synthetic copy
    // constructor created by the compiler.
    Handle<Dog> handle2;
    handle2 = handle1;
    handle2->val = 43;

    cout << "Handle1's val is " << (*handle1).val << endl;
    cout << "Handle2's val is " << (*handle2).val << endl;

    
    cout << "End." << endl;
    return 0;
}
