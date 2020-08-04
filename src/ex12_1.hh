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


    // explicit Str(size_type n, char c): data(n, c) { 

    // }


private:
    char* data;
};

ostream& operator<<(ostream& os, const StrV& s) {
    os << s.data;
    return os;                
}


#endif /* EX12_1_HH */
