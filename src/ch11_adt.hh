#ifndef CH11_ADT_HH
#define CH11_ADT_HH

#include <cstddef>
#include <memory>

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
        cout << "inside index operator non-const" << endl;
        return data[i];
    }

    const T& operator[](size_type i) const {
        cout << "inside index operator const" << endl;
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
        while (it != data) {
            alloc.destroy(it);
            it--;
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


#endif /* CH11_ADT_HH */
