// Ex 17: Program creates a file of Readings with 50 randomly generated temp 
//        readings. 

#include "Reading.cpp"
#include <random>
#include <fstream>

using namespace std;

int main() {
    // we want random numbers that look like 50.43, 70.63
    // generate random ints from 5000 to 9000, and divide by 100.
    default_random_engine engine;
    uniform_int_distribution<int> dist(5000,9000);

    string oname = "raw_temps.txt";
    ofstream ost {oname};
    if (!ost)
        throw runtime_error("can't open file");

    for (int i=0; i<2; ++i) {
        for (int j=0; j<24; ++j) {
            double d = dist(engine)/100.0;
            ost << Reading{j, d};
        }
    }

}