#ifndef EX14_4_HH
#define EX14_4_HH

template <>
std::vector<char>* clone(const std::vector<char>* vec) {
    return new std::vector<char>(*vec);
}

#endif /* EX14_4_HH */
