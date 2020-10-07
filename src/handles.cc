#include "handles.hh"
#include <vector>
#include <stdexcept>

using std::vector;
using std::runtime_error;
using std::size_t;

template <typename T>
T* clone(const T* tp) {
    return tp->clone();
}

template <>
std::vector<char>* clone(const std::vector<char>* vec) {
    return new std::vector<char>(*vec);
}


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

template <typename T>
T& RefHandle<T>::operator*() const {
    if (ptr) {
        return *ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

template <typename T>
T* RefHandle<T>::operator->() const {
    if (ptr) {
        return ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

template <typename T>
RefHandle<T>::~RefHandle() {
    (*refptr)--;
    if (refptr == 0) {
        delete refptr;
        delete ptr;
    }
}


// Copying increments the count which is shared between the instances.  ONLY
// copying does this.  Creating new RefHandles via the constructor RefHandle(T*)
// will just construct a totally new instance, which may destroy the object too
// soon.
template <typename T>
RefHandle<T>::RefHandle(const RefHandle& source): ptr(source.ptr), refptr(source.refptr) {
    ++*refptr;   // order prevents some need for parens, still means (*refptr)++
}


template <typename T>
RefHandle<T>& RefHandle<T>::operator=(const RefHandle& rhs) {
    // Very obscure:
    // This protects against self-assignment, because if it's the same object,
    // it gets its count incremented and then decremented meaning it stays static,
    // and therefore won't be destroyed in the following call.
    // As it needed to be incremented anyway, doing it here kills two birds with
    // one stone, so to speak.
    // This is quite tricky code.
    ++*(rhs.refptr);

    // Because we have been assigned to, we may need to delete our contents
    if (--*refptr == 0) {
        delete refptr;
        delete ptr;
    }

    refptr = rhs.refptr;   // No modifications needed here -- already done above.
    ptr = rhs.ptr;
    return *this;
}

template <typename T>
T& ControllableHandle<T>::operator*() const {
    if (ptr) {
        return *ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

template <typename T>
T* ControllableHandle<T>::operator->() const {
    if (ptr) {
        return ptr;
    } else {
        throw runtime_error("unbound handle");
    }
}

template <typename T>
ControllableHandle<T>::~ControllableHandle() {
    if (--*refptr == 0) {
        delete refptr;
        delete ptr;
    }
}

// See notes for RefHandle
template <typename T>
ControllableHandle<T>& ControllableHandle<T>::operator=(const ControllableHandle& rhs) {
    ++*(rhs.refptr);

    if (--*refptr == 0) {
        delete refptr;
        delete ptr;
    }

    refptr = rhs.refptr;
    ptr = rhs.ptr;
    return *this;
}
