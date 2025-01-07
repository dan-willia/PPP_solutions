#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

double one(double) { return 1; }

double slope(double x) { return 0.5*x; }

int main(int /*argc*/, char * /*argv*/[])
{
    Application app;
    Simple_window win({50, 50}, 600, 600, "Function graphs");

    constexpr int xmax = 600;                   // Window size
    constexpr int ymax = 600;

    constexpr int x_orig = xmax/2;              // Position of (0,0) is center of window
    constexpr int y_orig = ymax/2;
    constexpr Point orig {x_orig, y_orig};

    constexpr int r_min = -10;                  // range [-10:10]
    constexpr int r_max = 10;

    constexpr int n_points = 400;               // number of points used in range

    constexpr int x_scale = 20;                 // scaling factors
    constexpr int y_scale = 20;

    Function s {one, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s2 {slope, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s3 {[](double x) { return x*x; }, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s4 {[](double x) { return cos(x); }, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s5 {[](double x) { return cos(x) + slope(x); }, r_min, r_max, orig, n_points, x_scale, y_scale};
    s4.set_color(Color::blue);
    win.attach(s);
    win.attach(s2);
    win.attach(s3);
    win.attach(s4);
    win.attach(s5);

    Text s2_lab{Point{100, y_orig + 110}, "0.5x"};
    win.attach(s2_lab);

    constexpr int xlength = xmax*2/3;           // make axes 2/3 size of window
    constexpr int ylength = ymax*2/3;

    Axis x {Axis::x, Point{100, y_orig}, xlength, xlength/x_scale, "1==20 pixels" };
    x.set_color(Color::red);

    Axis y {Axis::y, Point{x_orig, ylength+100}, ylength, ylength/y_scale, "1==20 pixels" };
    y.set_color(Color::red);

    win.attach(x);
    win.attach(y);

    win.wait_for_button();
}
