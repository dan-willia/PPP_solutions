// Ex 5: Program reads strings and for each string outputs the character
// classification.

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void classify_chars(const string& str) {
    for (const char& ch : str) {
        if (isspace(ch))
            cout << ch << " is whitespace ('', '\\t', '\\n' etc.)" << endl;
        if (isalpha(ch))
            cout << ch << " is a letter ('a'...'z', 'A'...'Z') (note: not '_')" << endl;
        if (isdigit(ch))
            cout << ch << " is a decimal digit ('0'...'9')" << endl;
        if (isxdigit(ch))
            cout << ch << " is a hexadecimal digit ('a'...'f' or 'A'...'F')" << endl;
        if (isupper(ch))
            cout << ch << " is an uppercase letter" << endl;
        if (islower(ch))
            cout << ch << " is a lowercase letter" << endl;
        if (isalnum(ch))
            cout << ch << " is alphanumeric" << endl;
        if (iscntrl(ch))
            cout << ch << " is a control character (ASCII 0..31 and 127)" << endl;
        if (ispunct(ch))
            cout << ch << " is punctuation (i.e. not a letter, digit, whitespace, or invisible control character)" << endl;
        if (isprint(ch))
            cout << ch << " is printable (ASCII ''..'~')" << endl;
        if (isgraph(ch))
            cout << ch << " is a graph (letter, digit, or punctuation) (note: not space)" << endl;
    }
}

int main() {
    string iname = "Module1_htmlOverview.txt";
    ifstream is {iname};

    string test_string;
    while (is>>test_string) {
        classify_chars(test_string);
    }
}