#ifndef EX12_12_HH
#define EX12_12_HH

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

    explicit Vec(size_type n, const T& val) {
        create(n, val);
    }

    Vec(const Vec& source) {
        create(source.begin(), source.end());
    }

    Vec& operator=(const Vec& source) {
        if (&source != this) {
            uncreate();
            create(source.begin(), source.end());
        }

        return *this;
    }

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
        if (avail == limit) {   
            grow();
        }

        unchecked_append(val);
    }

    template <typename U>
    void insert(iterator position, U b, U e) {
        U pos_copy = b;
        size_type range_size = 0;

        while (pos_copy++ != e) { range_size++; }

        cout << "distance is " << range_size << endl;

        size_type remaining_space = limit - avail;
        cout << "remaining is " << remaining_space << endl;

        if (range_size > remaining_space) {
            cout << "need to reallocate" << endl;
            size_type new_size = (avail - data) + range_size;
            iterator new_data = alloc.allocate(new_size);
            iterator part1 = uninitialized_copy(data, position, new_data);
            iterator part2 = uninitialized_copy(b, e, part1);
            iterator part3 = uninitialized_copy(position, avail, part2);
            uncreate();
            data = new_data;
            avail = part3;
            limit = part3;
        } else {
            iterator new_start_pos = position + range_size - 1;
            size_type slice_size = avail - position;
            iterator new_end_pos = new_start_pos + slice_size;

            cout << "slice size is " << slice_size << endl;

            // starting from the back of the array, shunt the items downwards
            // pretty sure it has to happen from the back
            iterator it = avail;

            cout << "start loop" << endl;


            iterator write_pos = new_end_pos;
            while (it-- != position) {
                cout << *it << endl;
                *write_pos = *it;
                write_pos--;
            }

            uninitialized_copy(b, e, position);
            avail = new_end_pos + 1;
        }
    }


private:
    void create();
    void create(size_type n, const T& val);
    void create(const_iterator b, const_iterator e);
    void uncreate();
    void grow();
    void unchecked_append(const T& val);

    iterator data;
    iterator avail;
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
    if (data) {
        iterator it = avail;

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
    size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

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

#endif /* EX12_12_HH */
