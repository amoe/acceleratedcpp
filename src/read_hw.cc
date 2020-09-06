#include "read_hw.hh"

using std::istream;
using std::vector;

istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        double x;
        while (in >> x)
            hw.push_back(x);

        in.clear();
    }
    return in;
}
