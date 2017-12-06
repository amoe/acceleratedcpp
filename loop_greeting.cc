#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
    cout << "Please enter your first name: ";
    string name;
    cin >> name;   // read a single word name


    // This is the message, we can know its length at this point.
    const string greeting = "Hello, " + name + "!";

    const int greeting_height = 1;
    const int frame_height = 1;    // The top and the bottom use up one row each

    cout << "How much padding should I use? ";
    int requested_padding;
    cin >> requested_padding;

    // Padding applies to both the top and bottom of the greeting.
    // const int padding_top = 1;
    // const int padding_bottom = 1;
    // const int padding_left = 4;
    // const int padding_right = 4;

    // Note that these can still be const.
    const int padding_top = requested_padding;
    const int padding_bottom = requested_padding;
    const int padding_left = requested_padding;
    const int padding_right = requested_padding;
    
    const int padding_total = padding_top + padding_bottom;

    const int row_count = greeting_height + padding_total + (frame_height * 2);

    // Now we must calculate how to actually write a row.
    const int border_width = 1;


    // Note that this must be derived from size_type because this comes from
    // user input, outside the program.  C++ only guarantees that ints can
    // take values up to 32767.  (!)
    const string::size_type width
       = greeting.size() + (padding_left + padding_right) + (border_width * 2);


    //
    cout << endl;

    // Invariant: We have written r rows of output so far.

    // * <-- The invariant is true here: we have written 0 rows of output, and
    // r is equal 0.
    for (int r = 0; r != row_count; r++) {
        // We don't yet know how to write a real row.
        int c = 0;

        // invariant: we have written c characters so far in this row
        while (c != width) {

            // Are we about to write the greeting?
            if ((c == (border_width + padding_left) && r == (frame_height + padding_top)))  {
                // we should write the greeting and update c accordingly

                cout << greeting;
                c += greeting.size();
            } else {
                if (r == 0 || r == row_count - 1 || c == 0 || c == width - 1) {
                    // This is a border character.
                    cout << "*";
                } else {
                    cout << " ";
                }
                
                c++;
            }
        }

        cout << endl;

        // * <-- The invariant is false here, now we have written one more row.
        // * <--- Incrementing r makes the invariant true here.
    }

    // Now we also know that the invariant is true here..  Moreover we know that
    // we have written `row_count` rows because the loop condition implies such.
    // Therefore we've inductively demonstrated that we have fulfilled the
    // program brief to write `row_count` rows.
}
