#include "Point.cpp"

void drills1_6() {
    constexpr int birth_year = 1992;
    constexpr int age = 32;

    cout << "Dec: " << birth_year << '\t' 
         << "Hex: " << hex << birth_year << '\t' 
         << "Oct: " << oct << birth_year << 
    endl;

    cout << "Dec: " << dec << age << '\t' 
         << "Hex: " << hex << age << '\t' 
         << "Oct: " << oct << age << 
    endl;

    cout << dec;    // reset ostream to decimal 
}

void drill8() {

    int a, b, c, d;

    cin >> a >> oct >> b >> hex >> c >> d; // read a as dec, b as oct, c and d as hex values
    cout << a << '\t' << b << '\t' << c << '\t' << d << endl;   // output all as dec
}

void drill9() {
    constexpr double d = 1234567.89;

    cout << defaultfloat << d << '\t'
         << fixed << d << '\t'
         << scientific << d << '\t' <<
    endl;

    // fixed has most accurate representation in this case
    // default float includes 6 digits
    // scientific includes 6 digits after the decimal in the mantissa part
    // fixed includes six digits after the decimal of the original representation
}

void drill10() {
    constexpr int lastNamesWidth = 10;
    constexpr int firstNamesWidth = 12;
    constexpr int phoneNumbersWidth = 12;
    constexpr int emailsWidth = 28;

    vector<string> lastNames = {"Williams", "Camasta", "O'Neil", "Williams", "Williams", "Klemme"};
    vector<string> firstNames = {"Daniel", "Laura", "Connor", "Bob", "Adele", "Graham"};
    vector<string> phoneNumbers = {"3194094827", "0926181756", "3195212705", "3194310995", "3196407859", "3195417024"};
    vector<string> emails = {"dan.willa@yahoo.com", "lauramarieoc@gmail.com", "conjoneil@gmail.com", "rhwilli@yahoo.com", "adelewilliams282@yahoo.com", "graham.klemme@gmail.com"};

    cout << setw(lastNamesWidth) << "LAST NAME" 
         << setw(firstNamesWidth) << "FIRST NAME" 
         << setw(phoneNumbersWidth) << "PHONE" 
         << setw(emailsWidth) << "EMAIL" <<
    endl;

    for (int i=0; i<lastNames.size(); i++) {
        cout << setw(lastNamesWidth) << lastNames[i]
             << setw(firstNamesWidth) << firstNames[i]
             << setw(phoneNumbersWidth) << phoneNumbers[i]
             << setw(emailsWidth) << emails[i] <<
        endl;
    }
}

void drills11_17() {
    cout << "Input seven (x,y) pairs, followed by 'xx': ";

    vector<Point> original_points;
    Point p;
    while (cin>>p)
        original_points.push_back(p);

    cout << "Printing original points...\n";
    for (Point p : original_points) 
        cout << p;

    string oname = "mydata.txt";
    ofstream ost {oname};
    if (!ost)
        error("can't open output file ",oname);

    for (Point p : original_points)
        ost << p;

    string iname = "mydata.txt";
    ifstream ist {iname};
    if (!ist)
        error("can't open input file ",iname);

    vector<Point> processed_points;
    for (Point p; ist>>p;)
        processed_points.push_back(p);

    cout << "Printing processed points...\n";
    for (Point p : processed_points) 
        cout << p;

    // Check that origial points and processed points are the same
    if (original_points.size() != processed_points.size())
        cout << "Something's wrong!" << endl;
    for (int i=0; i<original_points.size(); ++i) {
        if (original_points[i] != processed_points[i])
            cout << "Something's wrong!" << endl;
    }
}

int main() {
    drill9();
}