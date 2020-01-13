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
