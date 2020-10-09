#ifndef EX14_5_HH
#define EX14_5_HH

template <>
std::vector<char>* clone(const std::vector<char>* vec) {
    return new std::vector<char>(*vec);
}

class Str {
    friend std::istream& operator>>(std::istream&, Str&);
    
public:
    using iterator = std::vector<char>::iterator;
    
    Str& operator+=(const Str& s) {
        data.make_unique();
        std::copy(s.data->begin(), s.data->end(), std::back_inserter(*data));
        return *this;
    }

    Str(const char* cp): data(new std::vector<char>) {
        std::size_t length = strlen(cp);
        copy(cp, cp + length, std::back_inserter(*data));
    }

    // dual iterator constructor
    template <typename T>
    Str(T b, T e) {
        
    }


    using size_type = std::vector<char>::size_type;

    size_type size() const {
        return data->size();
    }

    // Because this can be used as an lvalue, we must call make_unique.
    // Note that char& is now a reference.
    char& operator[](size_type i) {
        data.make_unique();
        return (*data)[i];
    }

    const char operator[](size_type i) const {
        return (*data)[i];
    }

    int get_refcount() const {
        return data.get_refcount();
    }
    
    Str substr(size_type pos, size_t len) const {
        iterator start = data->begin() + pos;
        return Str(start, start + len);
    }
    
private:
    ControllableHandle<std::vector<char>> data;
};

Str operator+(const Str& x, const Str& y) {
    Str result = x;
    result += y;
    return result;
}

std::ostream& operator<<(std::ostream& os, const Str& s) {
    for (Str::size_type i = 0; i < s.size(); i++) {
        os << s[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, Str& s) {
    s.data.make_unique();
    s.data->clear();
    char c;

    bool last_char_space = true;
    
    while (is.get(c) && std::isspace(c)) {
    }

    if (is) {
        do {
            s.data->push_back(c);
        } while (is.get(c) && !std::isspace(c));

        if (is) {
            is.unget();
        }
    }

    return is;
}

#endif /* EX14_5_HH */
