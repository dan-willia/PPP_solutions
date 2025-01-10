#include "/Users/daniel/Desktop/Misc_Courses/C++/std_lib_facilities.h"

struct Point {
    double x, y;
    Point() : x{0}, y{0} {};
    Point(double x, double y);
};

Point::Point(double xx, double yy)
    : x{xx}, y{yy} {}

bool operator==(Point& p1, Point& p2) {
    return p1.x==p2.x && p1.y==p2.y;
}

bool operator!=(Point& p1, Point& p2) {
    return !(p1==p2);
}

ostream& operator<<(ostream& os, const Point& p) {
    return os << '(' << p.x << ',' << p.y << ')' << endl;
}

istream& operator>>(istream& is, Point& p) {
    // example of valid format: (1.5,3.5)
    double x, y;
    char ch1, ch2, ch3;
    is >> ch1 >> x >> ch2 >> y >> ch3;
    if (!is)
        return is;
    if (ch1!='('||ch2!=','||ch3!=')') {     // oops: format error
        is.clear(ios::failbit);
        return is;
    }
    p = Point(x,y);
    return is;
}