#ifndef CH11_ADT_HH
#define CH11_ADT_HH

#include <cstddef>

using std::size_t;

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

private:
    void create() {
    };

    void create(size_type n, T val) {
    }

    // Points at the first item of the array.
    T* data;

    // Points one past the last item of the array.
    T* limit;
};

#endif /* CH11_ADT_HH */
