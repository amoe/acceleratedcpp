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
    }

    explicit StrV(const char* b) {
        size_t input_size = strlen(b);
        data = new char[input_size];
        copy(b, b + input_size, data);
    }


    explicit StrV(size_t n, char c) { 
        data = new char[n];
        for (size_t i = 0; i < n; i++) {
            *(data + i) = c;
        }
    }

private:
    char* data;
};

ostream& operator<<(ostream& os, const StrV& s) {
    os << s.data;   // XXX this is wrong because we shouldn't be using nul terminators
    return os;                
}


#endif /* EX12_1_HH */
