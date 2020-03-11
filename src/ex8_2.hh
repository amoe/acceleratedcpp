#include <iostream>

using std::cout;
using std::endl;

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
// No, this won't happen.  The type won't be passed by reference unless the
// formal parameters have & in the type.  So if I used `U&`, the caller *would*
// 'accidentally' pass their reference in, but there's nothing template-specific
// about that behaviour.
template <typename T, typename U>
U my_accumulate(T b, T e, U t) {
    while (b != e) {
        t += *b;
        b++;
    }

    return t;
}


// Somewhat complicated, the key being that we need the ability to copy the
// iterator in order to do the hypothetical check.
// Doesn't work for std::string because the == operator isn't defined there.
template <typename T, typename U>
T my_search(T haystack_begin, T haystack_end, U needle_begin, U needle_end) {
    while (haystack_begin != haystack_end) {
        if (*haystack_begin == *needle_begin) {
            T cursor1(haystack_begin);
            U cursor2(needle_begin);
            bool matched = true;
            
            while (cursor1 != haystack_end && cursor2 != needle_end) {
                if (*cursor1 != *cursor2) {
                    matched = false;
                    break;
                }

                cursor1++;
                cursor2++;
            }

            if (matched && cursor2 == needle_end) {
                break;
            }
        }

        haystack_begin++;
    }

    return haystack_begin;
}


template <typename T, typename U>
T my_find_if(T b, T e, U p) {
    while (b != e) {
        if (p(*b) != false) {
            return b;
        }

        b++;
    }

    return b;
}

template <typename T, typename U, typename V>
U my_remove_copy(T b, T e, U d, V t) {
    while (b != e) {
        if (*b != t) {
            *d = *b;
        }

        b++;
        d++;
    }

    return d;
}

// The key to this function is taking copies of iterators similar to search().
template <typename T, typename U>
T my_remove(T b, T e, U t) {
    T result = b;

    while (b != e) {
        if (*b != t) {
            // Copy it in if it wasn't specified to be removed.
            *result = *b;
            result++;
        }

        b++;

    }

    return result;
}


// U is a predicate

// The key here is to use swap, which is in <algorithm>.  We can't actually
// write the swap function ourselves, AFAICT.  Well we can, but only
// by calling out to another template (std::swap).
template <typename T, typename U>
T my_partition(T b, T e, U p) {
    T next_true = b;

    while (b != e) {
        if (p(*b)) {
            swap(*b, *next_true);
            next_true++;
        }

        b++;
    }

    return next_true;
}
