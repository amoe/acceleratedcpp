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

// Because of the way the URL finder operates, we have to disambiguate URLs
// with angle brackets, as below.

const string text_with_urls = R"(
While the gentleman enjoyed visiting http://www.google.com, he was also known to
visit http://reddit.com/r/s1 and <http://reddit.com/r/s2>.  He had one friend who
visited http://facebook.com/ and another who also visited <http://facebook.com/>.
There were some friends who visited no websites at all.  Those friends were
often mocked by those who visited <http://www.twitter.com/>.  Those who visited
http://www.twitter.com/ were noted to be angrier than usual.
)";

// A cross reference table is a mapping between distinct URLs and distinct
// lines on which those URLs were seen to occur.
using CrossReferenceTable = map<string, map<int, bool>>;

CrossReferenceTable xref(istream& in) {
    CrossReferenceTable result;
    int line_number = 1;
    string line;

    using iter_t = vector<string>::const_iterator;

    while (getline(in, line)) {
        vector<string> found_urls = find_urls(line);

        for (iter_t it = found_urls.begin(); it != found_urls.end(); it++) {
            result[*it][line_number] = true;
        }
        
        line_number += 1;
    }

    return result;
}

void print_xref_table(CrossReferenceTable the_xref) {
    using iter1_t = CrossReferenceTable::const_iterator;
    using iter2_t = map<int, bool>::const_iterator;

    for (iter1_t it1 = the_xref.begin(); it1 != the_xref.end(); it1++) {
        cout << "Found URL: " << it1->first << endl;

        map<int, bool> references = it1->second;
        for (iter2_t it2 = references.begin(); it2 != references.end(); it2++) {
            cout << "line reference is " << it2->first << endl;
        }
    }
}


int main() {
    stringstream sin(text_with_urls);

    cout << "Generating xref" << endl;

    CrossReferenceTable url_table = xref(sin);
    print_xref_table(url_table);

    cout << "Done" << endl;

    return 0;
}
