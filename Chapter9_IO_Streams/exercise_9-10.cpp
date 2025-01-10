// Ex 9: Write split function that takes a string and returns a vector of white-
//       space separated substrings.
// Ex 10: Write split function that takes two strings and returns a vector of
//        white-space separated substrings from the first string, where white
//        space is defined as "ordinary whitespace" plus the characters in the
//        second string.

#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

vector<string> split(const string& s) {
    vector<string> v;
    string cur_str;
    for (const char& ch : s)
        if (!isspace(ch))
            cur_str += ch;
        else 
            if (!cur_str.empty()) {
                v.push_back(cur_str);
                cur_str = "";
            }
    if (!cur_str.empty())
        v.push_back(cur_str);

    return v;
}

vector<string> split(const string& s, const string& w) {
    vector<string> v;
    string cur_str;
    unordered_set<char> w_set(w.begin(), w.end());  // Convert w to a set for O(1) lookup

    for (const char& ch : s)
        if (!(isspace(ch) || w_set.find(ch) != w_set.end())) {
            cur_str += ch;
        }
        else 
            if (!cur_str.empty()) {
                v.push_back(move(cur_str));
                cur_str.clear();
            }

    if (!cur_str.empty())
        v.push_back(cur_str);

    return v;
}

void print_vec(vector<string> v) {
    for (string s : v)
        cout << s << " ";
}

int main() {
    string test = "Hello, world! This:is a test.";
    string w = ",:.!";
    vector<string> v = split(test,w);
    print_vec(v);
}