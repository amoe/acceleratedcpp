#include <iostream>

int main() {
    std::cout << "Please enter your first name: ";
    std::string name;
    std::cin >> name;   // read a single word name


    // This is the message, we can know its length at this point.
    const std::string greeting = "Hello, " + name + "!";

    const int greeting_height = 1;
    const int frame_height = 2;    // The top and the bottom use up one row each


    // Padding applies to both the top and bottom of the greeting.
    const int padding_top = 1;
    const int padding_bottom = 1;
    
    const int padding_total = padding_top + padding_bottom;

    const int row_count = greeting_height + padding_total + frame_height;


    //
    std::cout << std::endl;
    int r = 0;

    // Invariant: We have written r rows of output so far.


    // * <-- The invariant is true here: we have written 0 rows of output, and
    // r is equal 0.
    while (r != row_count) {
        // We don't yet know how to write a real row.
        std::cout << std::endl;

        // * <-- The invariant is false here, now we have written one more row.
        ++r;
        
        // * <--- Incrementing r makes the invariant true here.
    }

    // Now we also know that the invariant is true here..  Moreover we know that
    // we have written `row_count` rows because the loop condition implies such.
    // Therefore we've inductively demonstrated that we have fulfilled the
    // program brief to write `row_count` rows.
}
