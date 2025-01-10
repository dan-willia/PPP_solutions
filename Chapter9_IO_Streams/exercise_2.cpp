#include "/Users/daniel/Desktop/Misc_Courses/C++/std_lib_facilities.h"

// Ex 2: Given a file name and a word outputs each line that contains
// that word together with the line number.

// returns vector with lowercased words from line
vector<string> get_words(string& line) {
    vector<string> v;
    istringstream iss {line};
    string cur_word;
    char ch;
    while (iss.get(ch)) {
        ch = tolower(ch);
        if (isalnum(ch))
            cur_word += ch;
        else {
            if (cur_word != "") {
                v.push_back(cur_word);
                cur_word = "";
            }
        }
    }
    if (cur_word != "")
        v.push_back(cur_word); // store last word in line

    return v;
}

bool contains_word(vector<string>& v, string& check_word) {
    for (const string& s : v)
        if (s == check_word)
            return true;
    return false;
}

int main() {
    string iname = "Module1_htmlOverview.txt";
    ifstream is {iname};

    string oname = "lines_with_word.txt";
    ofstream os {oname};

    if (!is || !os)
        error("Can't read input or output files");

    string line;
    string word = "html"; // word must be in all lowercase
    int count = 1;
    while (getline(is, line)) {
        vector<string> v = get_words(line);
        if (contains_word(v, word))
            cout << count << " " << line << endl;
        count++;
    }
}