#ifndef EX12_1_HH
#define EX12_1_HH

#include <cstring>

using std::ostream;
using std::cout;
using std::endl;
using std::copy;

class StrV {
    friend ostream& operator<<(ostream&, const StrV&);

public:
    using size_type = size_t;

    explicit StrV() {
        data = new char[0];
        avail = data;
    }

    explicit StrV(const char* b) {
        size_t input_size = strlen(b);
        data = new char[input_size];
        copy(b, b + input_size, data);
        avail = data + input_size;
    }


    explicit StrV(size_t n, char c) { 
        data = new char[n];
        avail = data;
        for (size_t i = 0; i < n; i++) {
            *(avail++) = c;
        }
    }


    // Range constructor
    // Because b and e are input iterators, we can't preallocate the whole
    // string, because we don't know the size until we add data.
    template <typename T>
    StrV(T b, T e) {
        size_t seen_so_far = 0;

        // Initialization to null is crucial here because delete[] is
        // defined to be a no-op, allowing us to skip a conditional.
        data = 0;

        while (b != e) {
            size_t new_size = seen_so_far + 1;
            char* new_data = new char[new_size];
            copy(data, data + seen_so_far, new_data);
            delete[] data;
            data = new_data;
            avail = new_data + new_size;

            // avail points one past the end
            *(avail - 1) = *b;
            seen_so_far = new_size;
            b++;
        }
    }


private:
    char* data;
    char* avail;
};

ostream& operator<<(ostream& os, const StrV& s) {
    char* position = s.data;
    while (position != s.avail) {
        os << *position;
        position++;
    }
    return os;                
}


#endif /* EX12_1_HH */
