// Ex 18: Program reads data file of Readings ("raw_temps.txt") into a vector
//        calculates mean and median temps.

#include "Reading.cpp"
#include <fstream>

using namespace std;

double median(vector<double> v) {
    if (v.size() % 2 == 0) {
        double med = (v[v.size()/2] + v[v.size()/2 - 1])/2;
        return med;
    }
    else {
        double med = v[v.size()/2];
        return med;
    }
}

int main() {
    string iname = "raw_temps.txt";
    ifstream ist {iname};
    if (!ist)
        throw runtime_error("can't read file");

    int hour = -7;
    double temperature = -7777;
    vector<Reading> v{};
    while (ist >> hour >> temperature) {
        if (hour < 0 || hour > 24)
            throw runtime_error("can't read file");
        v.push_back(Reading{hour, temperature});
    }

    vector<double> temps{};
    for (const Reading& r : v)
        temps.push_back(r.temperature);

    double sum = 0;
    for (const double& d : temps)
        sum += d;
    double mean = sum/temps.size();

    double med = median(temps);

    cout << "Mean: " << mean << endl;
    cout << "Median: " << med << endl;

}