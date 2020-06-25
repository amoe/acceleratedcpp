#ifndef CH11_ADT_HH
#define CH11_ADT_HH

#include <cstddef>

using std::cout;
using std::endl;
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
    void create() {
    };

    void create(size_type n, T val) {
    }

    // TODO: Some version which takes two iterators?
    /*
    void create(size_type n, T val) {
    }
    */

    void uncreate() {
    }

    // Allocate 2* more space than we need.
    void grow();

    // Append the value, assuming we already have enough space.
    void unchecked_append(const T& val) {
        
    }

    // Points at the first item of the array.
    iterator data;

    // Points at the last allocated item.
    iterator avail;

    // Points one past the last item of the array.
    iterator limit;
};

#endif /* CH11_ADT_HH */
