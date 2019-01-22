#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

using std::vector;
using std::string;
using std::accumulate;

string concat_all(vector<string> v) {
    return accumulate(v.begin(), v.end(), string());
}

int main() {
    vector<string> components = {
        "foo", "bar", "baz"
    };

    string foo = concat_all(components);

    // "foobarbaz"
    std::cout << foo << std::endl;

    return 0;
}
