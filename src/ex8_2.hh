// XXX: Is this actually safe?  What happens if we fall off the end of b2?
template <typename T, typename U>
bool my_equal(T b, T e, U b2) {
    // Simple linear search.
    while (b != e) {
        if (*b != *b2) {
            return false;
        }

        b++;
        b2++;
    }

    return true;
}

template <typename T, typename U>
T my_find(T b, T e, U t) {
    while (b != e && *b != t) {
        b++;
    }

    return b;
}


template <typename T, typename U>
T my_copy(T b, T e, U d) {
    while (b != e) {
        *d++ = *b++;
    }

    return b;
}
