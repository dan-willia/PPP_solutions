#include "/Users/daniel/Desktop/Misc_Courses/C++/std_lib_facilities.h"
#include <unordered_set>

const unordered_set<char> invalid_chars{';', ':', '"', '\'', '[', ']', '&', '^', '%', '$', '#', '@', '!'};

bool contains_chars(const string& str, const unordered_set<char>& chars) {
    for (char c : str) {
        if (chars.find(c) != chars.end())
            return true;
    }
    return false;
}

class Person {
public:
    Person() : fname{"no"}, lname{"name"}, age{1} {}     
    Person(string ffname, string llname, int aage);

    bool is_valid();

    string get_fname() const { return fname; }
    string get_lname() const { return lname; }
    int get_age() const { return age; }

private:    
    string fname;
    string lname;
    int age;
};

Person::Person(string ffname, string llname, int aage) 
    : fname{ffname}, lname{llname}, age{aage}
{
    if (!is_valid())
        throw runtime_error("Invalid person: " + fname + " " + lname);
}

bool Person::is_valid() {
    if (fname.empty() || lname.empty())
        return false;
    if (age <= 0 || age > 150)
        return false;
    if (contains_chars(fname, invalid_chars) || contains_chars(lname, invalid_chars))
        return false;
    return true;
}

ostream& operator<<(ostream& os, const Person& p) {
    os << p.get_fname() << " " << p.get_lname() << " " << p.get_age() << " ";
    return os;
}

istream& operator>>(istream& is, Person& p) {
    // assume format: name age
    string fname;
    string lname;
    int age;
    if (is >> fname >> lname >> age) {
        try {
            p = Person{fname, lname, age};
        }
        catch (const runtime_error& e) {
            cerr << e.what() << endl;
            is.clear(ios_base::failbit);
        }
    }
    return is;
}

int main()
try
{
    Person p;
    cout << "Enter: " << endl;
    while (cin >> p) {
        cout << p << endl;
    }
}
catch(const exception& e) {
    cerr << "An unexpected error occurred: " << e.what() << endl;
}