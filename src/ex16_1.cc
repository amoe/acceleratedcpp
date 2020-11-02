#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::endl;
using std::cout;

int main() {
    vector<string> a;
    // marker
    a.push_back("#include <iostream>");
    a.push_back("#include <vector>");
    a.push_back("#include <string>");
    a.push_back("");
    a.push_back("using std::string;");
    a.push_back("using std::vector;");
    a.push_back("using std::endl;");
    a.push_back("using std::cout;");
    a.push_back("");
    a.push_back("int main() {");
    a.push_back("    vector<string> a;");
    a.push_back("    // marker");
    a.push_back("    for (vector<string>::const_iterator it1 = a.begin(); it1 != a.end(); it1++) {");
    a.push_back("        cout << *it1 << endl;");
    a.push_back("");
    a.push_back("        if (*it1 == \"    // marker\") {");
    a.push_back("            for (vector<string>::const_iterator it2 = a.begin(); it2 != a.end(); it2++) {");
    a.push_back("                cout << \"a.push_back(\\\"\" << *it2 << \\\"\");\" << endl;");
    a.push_back("            }");
    a.push_back("        }");
    a.push_back("    }");
    a.push_back("    for (vector<string>::const_iterator it1 = a.begin(); it1 != a.end(); it1++) {");
    a.push_back("        cout << *it1 << endl;");
    a.push_back("    }");
    a.push_back("}");

    for (vector<string>::const_iterator it1 = a.begin(); it1 != a.end(); it1++) {
        cout << *it1 << endl;

        if (*it1 == "    // marker") {
            for (vector<string>::const_iterator it2 = a.begin(); it2 != a.end(); it2++) {
                cout << "    a.push_back(\"" << *it2 << "\");" << endl;
            }
        }
    }
}
