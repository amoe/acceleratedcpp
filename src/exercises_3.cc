// exercises_3.cc
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::vector;

// This is buggy as shit, it leaves off the last element.  :/
void ex3_2_quartiles() {
    vector<int> input;
    input.push_back(1);
    input.push_back(9);
    input.push_back(7);
    input.push_back(2);
    input.push_back(5);
    input.push_back(8);
    input.push_back(3);
    input.push_back(6);
    input.push_back(4);

    std::sort(input.begin(), input.end());

    int quartile_size = input.size() / 4;

    for (int i = 0; i < 4; i++) {
        std::cout << "[";

        for (int j = 0; j < quartile_size; j++) {
            std::cout << " " << input.at((i * quartile_size) +j) << " ";
        }

        std::cout << "]";
    }
    
    cout << endl;
}

void ex3_3_count_distinct_words() {

    vector<string> input;
    input.push_back("the");
    input.push_back("quick");
    input.push_back("brown");
    input.push_back("fox");
    input.push_back("jumped");
    input.push_back("over");
    input.push_back("the");
    input.push_back("lazy");
    input.push_back("dog");

    vector<string> seen;

    typedef vector<string>::size_type sz;


    for (sz i = 0; i < input.size(); i++) {
        string this_word = input.at(i);

        // Insanely dumb linear search to see if we already saw it.
        // But we don't have hash tables or `break` yet.
        // We cheated a bit by knowing that we can compare strings.
        // The smart solution sorts the vector and keeps two index counters.
        // However that also depends on knowing that you can meaningfully
        // sort string vectors (which is a larger assumption... maybe).
        bool is_already_seen = false;
        sz j = 0;
        while (!is_already_seen && j < seen.size()) {
            is_already_seen = (this_word == seen.at(j));
            j++;
        }

        if (is_already_seen) {
            // do nothing
        } else {
            seen.push_back(this_word);
        }
    }

    cout << "Total words was " << seen.size() << endl;
}

void ex3_4_longest_and_shortest() {
    vector<string> input;
    input.push_back("the");
    input.push_back("quick");
    input.push_back("brown");
    input.push_back("fox");
    input.push_back("jumped");
    input.push_back("over");
    input.push_back("the");
    input.push_back("lazy");
    input.push_back("dog");


    // We start off by taking the first element specially.  Because the max
    // or min of a 1 element set is always that item.
    // Zero items should be an error case.
    int max_length = input.at(0).size();
    int min_length = input.at(0).size();

    typedef vector<string>::size_type sz;
    
    for (sz i = 1; i < input.size(); i++) {
        int this_len = input.at(i).size();

        if (this_len > max_length)
            max_length = this_len;

        if (this_len < min_length)
            min_length = this_len;
    }

    std::cout << "Maximum length was " << max_length << endl;
    std::cout << "Minimum length was " << min_length << endl;
}

void ex3_6_divide_by_zero() {
    // This causes a floating point exception.
    int y = 3 / 0;
    std::cout << "y is now " << y << endl;
}

int main() {
    ex3_2_quartiles();
    ex3_3_count_distinct_words();
    ex3_4_longest_and_shortest();
    ex3_6_divide_by_zero();
}
