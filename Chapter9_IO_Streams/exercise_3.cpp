#include "/Users/daniel/Desktop/Misc_Courses/C++/std_lib_facilities.h"

// Ex 3: Remove all vowels from a file. 

constexpr int num_vowels = 10;
constexpr char vowels[10] = {'A','E','I','O','U','a','e','i','o','u'};

bool is_vowel(const char& ch) {
    for (int i=0; i<num_vowels; ++i)
        if (ch==vowels[i])
            return true;
    return false;
}

int main() {
    string isname = "Module1_htmlOverview.txt";
    ifstream is {isname};
    if (!is)
        error("can't open input file ", isname);

    string ostname = "disemvoweled_text.txt";
    ofstream ost {ostname}; 
    if (!ost)
        error("can't open output file ", ostname);

    char ch;
    while (is.get(ch)) {
        if (!is_vowel(ch))
            ost << ch;
    }
}