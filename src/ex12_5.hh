#ifndef EX12_5_HH
#define EX12_5_HH

#include <cstring>

using std::istream;
using std::ostream;
using std::cout;
using std::endl;

class StrV {
    friend ostream& operator<<(ostream&, const StrV&);
    friend istream& operator>>(istream&, StrV&);

public:
    using size_type = size_t;

    explicit StrV() {
        buffer = new char[1];
        avail = buffer;
    }

    explicit StrV(const char* b) {
        size_t input_size = strlen(b);
        buffer = new char[input_size + 1];
        std::copy(b, b + input_size, buffer);
        avail = buffer + input_size;
    }


    explicit StrV(size_t n, char c) { 
        buffer = new char[n + 1];
        avail = buffer;
        for (size_t i = 0; i < n; i++) {
            *(avail++) = c;
        }
    }

    template <typename T>
    StrV(T b, T e) {
        buffer = 0;
        avail = 0;

        initialize_from_iterator(b, e);
    }

    StrV(const StrV& source): StrV(source.buffer, source.avail) {
    }

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

    StrV& operator+=(const StrV& s) {
        initialize_from_iterator(s.buffer, s.avail);
        return *this;
    }

    StrV& operator+=(const char* s) {
        initialize_from_iterator(s, s + strlen(s));
        return *this;
    }

    bool operator!=(const StrV& s) {
        return !(*this == s);
    }

    bool operator==(const StrV& rhs) {
        int result = strcmp(this->c_str(), rhs.c_str());
        return result == 0;
    }

    bool operator>(const StrV& rhs) {
        int result = strcmp(this->c_str(), rhs.c_str());
        return result > 0;
    }

    bool operator<(const StrV& rhs) {
        int result = strcmp(this->c_str(), rhs.c_str());
        return result < 0;
    }

    bool operator<=(const StrV& rhs) {
        int result = strcmp(this->c_str(), rhs.c_str());
        return result <= 0;
    }

    bool operator>=(const StrV& rhs) {
        int result = strcmp(this->c_str(), rhs.c_str());
        return result >= 0;
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

    void push_back(char c) {
        size_t new_size = size() + 1;
        char* new_buffer = new char[new_size + 1];
        std::copy(buffer, avail, new_buffer);
        delete[] buffer;
        buffer = new_buffer;
        avail = new_buffer + new_size;

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

istream& operator>>(istream& is, StrV& s) {
    s.clear();
    char c;

    while (is.get(c)) {
        if (!isspace(c)) {
            is.unget();
            break;
        }
    }

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

StrV operator+(const char* a, const StrV& b) {
    cout << "inside overload1" << endl;

    StrV tmp(a);
    tmp += b;
    return tmp;
}

StrV operator+(const StrV& a, const char* b) {
    cout << "inside overload2" << endl;
    StrV tmp(a);
    tmp += b;
    return tmp;
}

#endif /* EX12_5_HH */
