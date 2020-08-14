#ifndef EX12_1_HH
#define EX12_1_HH

#include <cstring>

using std::istream;
using std::ostream;
using std::cout;
using std::endl;

class StrV {
    friend ostream& operator<<(ostream&, const StrV&);   // FIXME friend unnecessary
    friend istream& operator>>(istream&, StrV&);

public:
    using size_type = size_t;

    explicit StrV() {
        // It's no longer fine to not allocate here!  Because c_str()
        // needs to be valid for an empty string.
        buffer = new char[1];
        avail = buffer;
    }

    StrV(const char* b) {
        size_t input_size = strlen(b);
        buffer = new char[input_size + 1];   // reserve space for null
        std::copy(b, b + input_size, buffer);
        avail = buffer + input_size;
    }


    explicit StrV(size_t n, char c) { 
        buffer = new char[n + 1]; // reserve space for null
        avail = buffer;
        for (size_t i = 0; i < n; i++) {
            *(avail++) = c;
        }
    }

    // Range constructor
    // Because b and e are input iterators, we can't preallocate the whole
    // string, because we don't know the size until we add buffer.
    template <typename T>
    StrV(T b, T e) {

        // Initialization to null is crucial here because delete[] is
        // defined to be a no-op, allowing us to skip a conditional.
        buffer = 0;
        avail = 0;

        initialize_from_iterator(b, e);
    }

    // Copy constructor: Use range constructor to copy source
    StrV(const StrV& source): StrV(source.buffer, source.avail) {
    }

    // Assignment operator: 
    StrV& operator=(const StrV& source) {
        if (&source != this) {
            clear();
            initialize_from_iterator(source.buffer, source.avail);
        }

        return *this;
    }

    ~StrV() {
        clear();
    }

    // Like initialize_from_iterator, except that we do not clear first.
    StrV& operator+=(const StrV& s) {
        initialize_from_iterator(s.buffer, s.avail);
        return *this;
    }

    size_type size() {
        return avail - buffer;
    }

    char operator[](size_type i) {
        return buffer[i];
    }

    const char operator[](size_type i) const {
        return buffer[i];
    }

    const char* c_str() const {
        *avail = '\0';
        return buffer;
    }

    const char* data() const {
        return buffer;
    }

    size_t copy(char* s, size_t len) const {
        char* end = std::copy(buffer, buffer + len, s);
        return end - buffer;
    }

private:
    template <typename T>
    void initialize_from_iterator(T b, T e) {
        while (b != e) {
            push_back(*b);
            b++;
        }
    }

    // Not part of the string api but used internally.
    void push_back(char c) {
        size_t new_size = size() + 1;
        char* new_buffer = new char[new_size + 1];  // reserve space for null
        std::copy(buffer, avail, new_buffer);
        delete[] buffer;
        buffer = new_buffer;
        avail = new_buffer + new_size;

        // avail points one past the end
        *(avail - 1) = c;
    }

    void clear() {
        delete[] buffer;
        buffer = 0;
        avail = 0;
    }

    char* buffer;
    char* avail;
};

ostream& operator<<(ostream& os, const StrV& s) {
    char* position = s.buffer;
    while (position != s.avail) {
        os << *position;
        position++;
    }
    return os;                
}

// A variation, this one has two unget calls instead of one, but
// the logic is a bit more straightforward
istream& operator>>(istream& is, StrV& s) {
    s.clear();
    char c;

    // Fast forward over all space
    while (is.get(c)) {
        if (!isspace(c)) {
            is.unget();
            break;
        }
    }

    // Bail out now if we hit the end
    if (!is) return is;
    
    while (is.get(c)) {
        if (isspace(c)) {
            is.unget();
            break;
        }

        s.push_back(c);
    }
    
    return is;
}

StrV operator+(const StrV& a, const StrV& b) {
    StrV tmp = a;
    tmp += b;
    return tmp;
}

#endif /* EX12_1_HH */
