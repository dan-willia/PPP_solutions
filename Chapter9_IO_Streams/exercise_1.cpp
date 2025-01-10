#include "/Users/daniel/Desktop/Misc_Courses/C++/std_lib_facilities.h"

// Ex 1: Read a text file and convert input to lowercase, produce a new file.
int main() {
    string isname = "Module1_htmlOverview.txt";
    ifstream is {isname};
    if (!is)
        error("can't open input file ", isname);

    string ostname = "lower_text.txt";
    ofstream ost {ostname}; 
    if (!ost)
        error("can't open output file ", ostname);

    char ch;
    while (is.get(ch)) {
        char ch2 = tolower(ch);
        ost << ch2;
    }
}