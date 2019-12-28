#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "url_finder.hh"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::map;
using std::istream;
using std::vector;

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
    vector<string> result = find_urls(
        "Go to http://www.foo.com/bar/ and check out my ftp://site immediately"
    );

    cout << "found " << result.size() << " urls" << endl;

    for (auto url: result) {
        cout << "Found URL: " << url << endl;
    }


    stringstream sin(text_with_urls);

    cout << "Generating xref" << endl;

    CrossReferenceTable url_table = xref(sin);
    print_xref_table(url_table);

    cout << "Done" << endl;

    return 0;
}
