// Ex 11: Program reverses the order of characters in a text file.

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int main() 
try
{
    string iname = "Module1_htmlOverview.txt";
    ifstream is {iname};
    if (!is) 
        throw runtime_error("cannot open file");

    string oname = "reversed_Module1_htmlOverview.txt";
    ofstream os {oname};
    if (!os)
        throw runtime_error("cannot open file");

    char ch;
    vector<char> file_in_reverse;
    while (is >> noskipws >> ch) {
        file_in_reverse.push_back(ch);
    }
    for (int i=file_in_reverse.size()-1; i>=0; --i)
        os << file_in_reverse[i];
}
catch (runtime_error e) {
    cout << e.what() << endl;
}