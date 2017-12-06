#include <iostream>

int main() {
    std::cout << "Please enter your first name: ";
    std::string name;
    std::cin >> name;   // read a single word name


    // This is the message, we can know its length at this point.
    const std::string greeting = "Hello, " + name + "!";

    const int greeting_height = 1;
    const int frame_height = 1;    // The top and the bottom use up one row each

    // Padding applies to both the top and bottom of the greeting.
    const int padding_top = 1;
    const int padding_bottom = 1;
    const int padding_left = 1;
    const int padding_right = 1;
    
    const int padding_total = padding_top + padding_bottom;

    const int row_count = greeting_height + padding_total + (frame_height * 2);

    // Now we must calculate how to actually write a row.
    const int border_width = 1;


    // Note that this must be derived from size_type because this comes from
    // user input, outside the program.  C++ only guarantees that ints can
    // take values up to 32767.  (!)
    const std::string::size_type width
       = greeting.size() + (padding_left + padding_right) + (border_width * 2);


    //
    std::cout << std::endl;
    int r = 0;

    // Invariant: We have written r rows of output so far.


    // * <-- The invariant is true here: we have written 0 rows of output, and
    // r is equal 0.
    while (r != row_count) {
        // We don't yet know how to write a real row.
        int c = 0;

        // invariant: we have written c characters so far in this row
        while (c != width) {
            // There's no reason for us to only write 1 char on this iteration,
            // provided that we update c appropriately (and provided that we
            // make sure we don't go over `width`!

            if (r == 0 || r == row_count - 1 || c == 0 || c == width - 1) {
                // This is a border character.
                std::cout << "*";
                c++;
            } else {
                // do something else

                // We now have to work out if we should be writing the first
                // char of the greeting, if so write the entire greeting.
                
                if (c == (border_width + padding_left) && r == (frame_height + padding_top)) {
                    std::cout << greeting;
                    c += greeting.size();
                } else {
                    std::cout << " ";
                    c++;
                }
            }
        }

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
