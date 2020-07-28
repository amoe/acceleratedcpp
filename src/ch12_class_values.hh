#ifndef CH12_CLASS_VALUES_HH
#define CH12_CLASS_VALUES_HH

using std::list;
using std::cout;
using std::endl;
using std::copy;
using std::strlen;
using std::back_inserter;

class Str {
public:
    using size_type = Vec<char>::size_type;

    Str() { }

    Str& operator=(const Str& source) {
        cout << "inside assignment operator";
        data = source.data;
        return *this;
    }

    // Piggy back on the Vec constructor.
    Str(size_type n, char c): data(n, c) { }

    Str(const char* cp) {
        copy(cp, cp + strlen(cp), back_inserter(data));
    }

    // Copy from an iterator.
    template <typename T>
    Str(T b, T e) {
        copy(b, e, back_inserter(data));
    }

    char operator[](int i) {
        return data[i];
    }


    void print() {
        for (Vec<char>::const_iterator it = data.begin(); it != data.end(); it++) {
            cout << *it;
        }
        cout << endl;
    }

private:
    Vec<char> data;
};

#endif /* CH12_CLASS_VALUES_HH */
