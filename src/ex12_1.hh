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
