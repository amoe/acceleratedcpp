#include <iostream>
#include <string>
#include <sstream>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::map;
using std::istream;

const string text_with_urls = R"(
While the gentleman enjoyed visiting http://www.google.com, he was also known to
visit http://reddit.com/r/s1 and http://reddit.com/r/s2.  He had one friend who
visited http://facebook.com/ and another who also visited http://facebook.com.
There were some friends who visited no websites at all.  Those friends were
often mocked by those who visited http://www.twitter.com/.
)";

// A cross reference table is a mapping between distinct URLs and distinct
// lines on which those URLs were seen to occur.
using CrossReferenceTable = map<string, map<int, bool>>;


CrossReferenceTable xref(istream& in) {
    CrossReferenceTable result;
    return result;
}

void print_xref_table(CrossReferenceTable the_xref) {
}


int main() {
    stringstream sin(text_with_urls);

    cout << "Generating xref" << endl;

    CrossReferenceTable result = xref(sin);
    print_xref_table(result);

    cout << "Done" << endl;

    return 0;
}
