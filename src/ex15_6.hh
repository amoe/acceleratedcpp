#ifndef EX15_6_HH
#define EX15_6_HH

#include <list>
#include <cstddef>
#include <cstring>
#include <memory>

using std::strlen;
using std::list;
using std::ostream;
using std::list;
using std::cout;
using std::endl;
using std::copy;
using std::strlen;
using std::back_inserter;
using std::istream;
using std::max;
using std::cout;
using std::endl;
using std::size_t;
using std::allocator;
using std::uninitialized_copy;
using std::uninitialized_fill;

template <typename T> class Vec {
public:
    using iterator = T*;
    using const_iterator = const T*;
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;

    Vec() {
        create();
    }

    // K&M use a const reference to val instead of a plain val.
    // Is there any semantic difference between these?
    explicit Vec(size_type n, const T& val) {
        create(n, val);
    }

    // "The language allows us to omit the type parameters when we are
    // within the scope of the template."
    Vec(const Vec& source) {
        create(source.begin(), source.end());
    }

    // Argument indicates the right hand side, eg the source of assignment.
    Vec& operator=(const Vec& source) {
        // &source yields a pointer.  comparable to this pointer.
        if (&source != this) {
            uncreate();   // Free all storage we have already
            create(source.begin(), source.end());
        }

        return *this;
    }

    // Destructor
    ~Vec() {
        uncreate();
    }

    size_type size() const {
        return avail - data;
    }

    T& operator[](size_type i) {
        return data[i];
    }

    const T& operator[](size_type i) const {
        return data[i];
    }

    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    
    iterator end() { return avail; }
    const_iterator end() const { return avail; }

    void push_back(const T& val) {
        // We are guaranteed to eventually hit the limit as we can only
        // push_back a single element at a time.
        if (avail == limit) {   
            grow();
        }

        unchecked_append(val);
    }

    void clear();


private:
    // Construct a totally empty Vec with zero capacity
    void create();

    // Fill with a single value
    void create(size_type n, const T& val);

    // Copy from an existing iterator range
    void create(const_iterator b, const_iterator e);

    void uncreate();

    // Allocate 2* more space than we need.
    void grow();

    // Append the value, assuming we already have enough space.
    void unchecked_append(const T& val);

    // Points at the first item of the array.
    iterator data;

    // Points at the last allocated item.
    iterator avail;

    // Points one past the last item of the array.
    iterator limit;

    allocator<T> alloc;
};

template <typename T> void Vec<T>::create() {
    data = 0;
    avail = 0;
    limit = 0;
};

template <typename T> void Vec<T>::create(size_type n, const T& val) {
    data = alloc.allocate(n);
    iterator valid_end = data + n;

    limit = valid_end;
    avail = valid_end;

    uninitialized_fill(data, limit, val);
}

template <typename T> void Vec<T>::create(const_iterator b, const_iterator e) {
    data = alloc.allocate(e - b);
    iterator valid_end = uninitialized_copy(b, e, data);
    limit = valid_end;
    avail = valid_end;
}

template <typename T> void Vec<T>::uncreate() {
    // Destroy all items backwards

    // don't need to dealloc if nothing was ever allocated, and
    // deallocate won't work on a null pointer
    if (data) {
        iterator it = avail;

        // There is a subtlety here -- avail points at *ONE PAST* the last item.
        // Therefore we need to subtract 1 from the iterator BEFORE calling
        // destroy, and although we compare `it != data`, we still destroy
        // `data` itself (i.e. the item at index 0).
        while (it != data) {
            alloc.destroy(--it);
        }


        alloc.deallocate(data, limit - data);
    }

    data = 0;
    limit = 0;
    avail = 0;
}

template <typename T> void Vec<T>::grow() {
//    cout << "growing" << endl;

    // ptrdiff_t because both args of max must have same type.
    // The result is implicitly widened to size_type.
    // 1 is to deal with the case of an empty vector.
    size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

    // Temps needed here so that uncreate doesn't destroy the new storage.
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);

    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <typename T> void Vec<T>::unchecked_append(const T& val) {
    alloc.construct(avail, val);
    avail++;
}


template <typename T>
void Vec<T>::clear() {
    avail = data;
}


class Str {
    // Friend declarations are unaffected by access labels, so put them
    // at the start.
    friend istream& operator>>(istream&, Str&);

public:
    using size_type = Vec<char>::size_type;

    Str() { }

    Str& operator=(const Str& source) {
        cout << "inside assignment operator";
        data = source.data;
        return *this;
    }

    // the only operation we have is push_back so we just have to do that
    Str& operator+=(const Str& s) {
        for (Vec<char>::const_iterator it = s.data.begin(); it != s.data.end(); it++) {
            data.push_back(*it);
        }

        return *this;
    }


    // Piggy back on the Vec constructor.
    Str(size_type n, char c): data(n, c) { }

    Str(const char* cp) {
        copy(cp, cp + strlen(cp), back_inserter(data));
    }

    // Copy from an iterator.
    template <typename T>
    Str(T b, T e) {
        copy(b, e, back_inserter(data));
    }

    // Called when indexing non-const Str objects.
    char operator[](size_type i) {
        return data[i];
    }

    // Only used when indexing a Str object that is itself const.
    const char operator[](size_type i) const {
        return data[i];
    }

    void print() {
        for (Vec<char>::const_iterator it = data.begin(); it != data.end(); it++) {
            cout << *it;
        }
        cout << endl;
    }

    size_type size() const {
        return data.size();
    }

private:
    Vec<char> data;
};

Str operator+(const Str& x, const Str& y) {
    Str result = x;   // Make a non-const copy.
    result += y;
    return result;   // Also copy on returning.
}


istream& operator>>(istream& is, Str& s) {
    s.data.clear();
    char c;

    bool last_char_space = true;
    
    while (is.get(c) && isspace(c)) {
        // fast-forward over leading whitespace.  clever loop and a half here
    }

    if (is) {
        // do...while because we're reusing the already-existing value of 'c',
        // rather than ungetting it.
        do {
            s.data.push_back(c);
        } while (is.get(c) && !isspace(c));

        // We might have read some whitespace to terminate the previous loop,
        // which should still be there for the next reader.  OTOH, if we hit the
        // end, 'is' will be false, and this will not execute.
        if (is) {
            is.unget();
        }
    }

    return is;
}

ostream& operator<<(ostream& os, const Str& s) {
    for (Str::size_type i = 0; i < s.size(); i++) {
        os << s[i];
    }
    return os;
}

#endif /* EX15_6_HH */
