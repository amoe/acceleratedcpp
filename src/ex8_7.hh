#ifndef EX8_7_HH
#define EX8_7_HH

template <typename T>
T my_max(T a, T b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

template <typename T, typename U>
T my_max2(T a, U b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}


#endif /* EX8_7_HH */
