#ifndef EX12_11_HH
#define EX12_11_HH

#include <cstring>
#include <cstddef>
#include <memory>

using std::max;
using std::cout;
using std::endl;
using std::size_t;
using std::allocator;
using std::uninitialized_copy;
using std::uninitialized_fill;
using std::ostream;
using std::list;
using std::cout;
using std::endl;
using std::copy;
using std::strlen;
using std::back_inserter;
using std::istream;


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

    template <typename U>
    explicit Vec(U b, U e) {
        create(b, e);
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
        if (avail == limit) {   
            grow();
        }

        unchecked_append(val);
    }

    void clear();


private:
    void create();

    void create(size_type n, const T& val);

    template <typename U>
    void create(U b, U e) {
        // note that this requires a random access iterator
        data = alloc.allocate(e - b);
        iterator valid_end = uninitialized_copy(b, e, data);
        limit = valid_end;
        avail = valid_end;
    }


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

template <typename T>
void Vec<T>::clear() {
    avail = data;
}



class Str {
    friend istream& operator>>(istream&, Str&);

public:
    using size_type = Vec<char>::size_type;

    Str() { }

    Str& operator=(const Str& source) {
        data = source.data;
        return *this;
    }

    Str& operator+=(const Str& s) {
        for (Vec<char>::const_iterator it = s.data.begin(); it != s.data.end(); it++) {
            data.push_back(*it);
        }

        return *this;
    }


    Str(size_type n, char c): data(n, c) { }

    Str(const char* cp) {
        copy(cp, cp + strlen(cp), back_inserter(data));
    }

    template <typename T>
    Str(T b, T e): data(b, e) { }

    char operator[](size_type i) {
        return data[i];
    }

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
    Str result = x;
    result += y;
    return result;
}


istream& operator>>(istream& is, Str& s) {
    s.data.clear();
    char c;

    bool last_char_space = true;
    
    while (is.get(c) && isspace(c)) {
    }

    if (is) {

        do {
            s.data.push_back(c);
        } while (is.get(c) && !isspace(c));

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

#endif /* EX12_11_HH */
