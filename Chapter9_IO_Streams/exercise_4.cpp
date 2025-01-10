// Ex 4: User inputs several integers in any combination of octal, decimal,
// or hexadecimal; converts numbers to decimal form and prints in properly
// spaced columns. 

// Input is assumed to contain 0 or 0x base prefixes for oct and hex, respectively.

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

const string terminator = "|";

void validate_input(const string& str_num, const string terminator) {
    if (str_num == terminator)
        return;

    if (str_num[1] == 'x') {    // possible hex
        if (str_num[0] != '0') {
            throw runtime_error("Not a valid hex number");
        }
        for (const char& ch : str_num.substr(2))
            if (!isnumber(ch))
                throw runtime_error("Not a valid hex number");
    }
    else if (str_num[0] == '0') {    // possible oct
        for (const char& ch : str_num.substr(1))
            if (!isnumber(ch) || ch == '8' || ch == '9') {
                throw runtime_error("Not a valid oct number");
            }
    }
    else {
        for (const char& ch : str_num) // possible dec
            if (!isnumber(ch)) {
                throw runtime_error("Not a valid number");
            }
    }
}

int main() 
try
{
    string str_num;
    cout << "Enter a dec, hex, or oct digit: ";
    cin >> str_num;
    validate_input(str_num, terminator);

    while (str_num != terminator) {
        if (str_num[1] == 'x') { // str_num is hex
            int new_num;
            stringstream ss {str_num.substr(2)};
            ss >> hex >> new_num;
            cout << str_num << '\t' << "hexadecimal\t"<< "converts to   " << dec << new_num << "  decimal" << endl;
        }
        else if (str_num[0] == '0') { // str_num is oct
            int new_num;
            stringstream ss {str_num.substr(1)};
            ss >> oct >> new_num;
            cout << str_num << '\t' << "octal\t\t" << "converts to   " << dec << new_num << "  decimal" << endl;
        }
        else 
            cout << str_num << '\t' << "decimal\t\t" << "converts to   " << dec << str_num << "  decimal" << endl;
        cin >> str_num;
        validate_input(str_num, terminator);
    }
}
catch (runtime_error e) {
    cout << e.what() << endl;
}