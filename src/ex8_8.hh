#ifndef EX8_8_HH
#define EX8_8_HH

template <typename T, typename U>
bool binary_search(T begin, T end, const U& x) {
    while (begin < end) {
        T mid = begin + ((end - begin) / 2);
        if (x < *mid) {
            end = mid;
        } else if (*mid < x) {
            begin = mid + 1;
        } else {
            return true;
        }
    }

    return false;
}

#endif /* EX8_8_HH */
