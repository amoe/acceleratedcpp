#ifndef EX10_2_HH
#define EX10_2_HH

using std::vector;

template <typename T, typename U>
T generic_median(U begin, U end) {
    vector<T> temporary(begin, end);

    if (temporary.empty()) {
        throw std::domain_error("no sensible median");
    }
    using vec_sz = typename vector<T>::size_type;
    vec_sz size = temporary.size();

    sort(temporary.begin(), temporary.end());

    vec_sz mid = size / 2;

    if ((size % 2) == 0) {
        vec_sz e1 = mid;
        vec_sz e2 = mid - 1;
        return (temporary[e1] + temporary[e2]) / 2;
    } else {
        return temporary[mid];
    }
}

#endif /* EX10_2_HH */
