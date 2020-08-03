#ifndef CH12_CLASS_VALUES_HH
#define CH12_CLASS_VALUES_HH

using std::ostream;
using std::list;
using std::cout;
using std::endl;
using std::copy;
using std::strlen;
using std::back_inserter;
using std::istream;


class Str {
    // Friend declarations are unaffected by access labels, so put them
    // at the start.
    friend istream& operator>>(istream&, Str&);

public:
    using size_type = Vec<char>::size_type;

    Str() { }

    Str& operator=(const Str& source) {
        cout << "inside assignment operator";
        data = source.data;
        return *this;
    }

    // the only operation we have is push_back so we just have to do that
    Str& operator+=(const Str& s) {
        for (Vec<char>::const_iterator it = s.data.begin(); it != s.data.end(); it++) {
            data.push_back(*it);
        }

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

    // Called when indexing non-const Str objects.
    char operator[](size_type i) {
        return data[i];
    }

    // Only used when indexing a Str object that is itself const.
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
    Str result = x;   // Make a non-const copy.
    result += y;
    return result;   // Also copy on returning.
}


istream& operator>>(istream& is, Str& s) {
    s.data.clear();
    char c;

    bool last_char_space = true;
    
    while (is.get(c) && isspace(c)) {
        // fast-forward over leading whitespace.  clever loop and a half here
    }

    if (is) {
        // do...while because we're reusing the already-existing value of 'c',
        // rather than ungetting it.
        do {
            s.data.push_back(c);
        } while (is.get(c) && !isspace(c));

        // We might have read some whitespace to terminate the previous loop,
        // which should still be there for the next reader.  OTOH, if we hit the
        // end, 'is' will be false, and this will not execute.
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


#endif /* CH12_CLASS_VALUES_HH */
