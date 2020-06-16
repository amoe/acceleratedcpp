#ifndef EX10_2_HH
#define EX10_2_HH

template <typename T>
double generic_median(T begin, T end) {
    // There is a small bug here which is that ptrdiff_t cannot store
    // the size of all arrays :(
    std::ptrdiff_t size = end - begin;

    if (size == 0) {
        throw std::domain_error("no sensible median");
    }

    std::sort(begin, end);

    std::ptrdiff_t mid = size / 2;

    if ((size % 2) == 0) {
        T e1 = begin + mid;
        T e2 = begin + (mid - 1);

        return (*e1 + *e2) / 2;
    } else {
        return *(begin + mid);
    }
}

#endif /* EX10_2_HH */
