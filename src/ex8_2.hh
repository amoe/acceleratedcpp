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


// Could V be a function type parameterized by T?  Probably not
template <typename T, typename U, typename V>
U my_remove_copy_if(T b, T e, U d, V p) {
    while (b != e) {
        bool result = p(*b);
        if (!result)
            *d = *b;

        b++;
        d++;
    }

    return d;
}

// Transform is just map.
template <typename T, typename U, typename V>
U my_transform(T b, T e, U d, V f) {
    while (b != e) {
        // AFAICS it's impossible to store the variable here, because
        // we can't write the type.  On the other hand, even if we could write
        // the type using auto, does it actually make sense to do any operations
        // on it?  Because it might be fully parametrically polymorphic.
        *d = f(*b);
        b++;
        d++;
    }

    return d;
}

// Several notable points here.
// We parameterize the return type, and it's not just an iterator.
// Here it's probably a numeric type like int or double.
// The type U needs to support the + operator.
// I'm not sure on this point: 
//   Hopefully, the type U is passed by-value, because otherwise += could modify
//   the caller's value of t -- couldn't it?
template <typename T, typename U>
U my_accumulate(T b, T e, U t) {
    while (b != e) {
        t += *b;
        b++;
    }

    return t;
}
