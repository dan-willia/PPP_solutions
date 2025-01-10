// Ex 6: Program reaplces punctuation with whitespace.
// Ex 7: Program extended to replace "don't" with "do not", leaves hyphens
//       within words intact, and converts all characters to lowercase.

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string process_string(const string& str) {
    // removes punctuation and lowers alpha chars
    string ret;
    if (str=="-")
        return ret;

    for (const char& ch : str) {
        if (!(ch=='.' || ch==';' || ch==',' || ch=='?' || ch=='\'' || ch== ':'))
            ret += tolower(ch);
        else
            ret += " ";
    }  
    return ret;
}

int main() {
    // removes all punctuation except double quotes and interior hyphens
    // provides example of how to expand contractions

    string test = "\" - Ms., don't!!! use the as-if rule...\"";
    string test2 = "Module1_htmlOverview.txt";
    ifstream is {test2};

    string output;
    istringstream ss {test2};
    string s;

    while (is>>s) {
        if (s.find("don't") != s.npos)
            s = "do not";
        s = process_string(s);
        output += s + " ";
    }
    cout << output << endl;
}