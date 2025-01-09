#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

// Ex 2-3: Create a Fct class that stores its constructor arguments
template <typename PrecisionType>
struct Fct : Open_polyline {
    Fct(std::function<double(double)> ff, double rr1, double rr2, Point oorig, int ccount = 100, double xxscale = 25, double yyscale = 25, double pprecision = 1.0)
        : f{ff}, r1{rr1}, r2{rr2}, orig{oorig}, count{ccount}, xscale{xxscale}, yscale{yyscale}, precision{pprecision}
    {
        if (r2 - r1 <= 0)
            error("bad graphing range");
        if (count <= 0)
            error("non-positive graphing count");
        count = static_cast<int>(r2 - r1) / precision;
        if (count <=0)
            error("precision too large for the given range");
        double dist = (r2 - r1) / count;
        double r = r1;
        for (int i = 0; i < count; ++i) {
            add(Point{orig.x + int(r * xscale), orig.y - int(f(r) * yscale)});
            r += dist;
        }
    }

    void set_fct(std::function<double(double)> new_f) { f = new_f; }
    void set_r1(double new_r1) { r1 = new_r1; }
    void set_r2(double new_r2) { r2 = new_r2; }
    void set_orig(Point new_orig) { orig = new_orig; }
    void set_count(int new_count) { count = new_count; }
    void set_xscale(double new_xscale) { xscale = new_xscale; }
    void set_yscale(double new_yscale) { yscale = new_yscale; }
    void set_precision(PrecisionType new_precision) {
        if (new_precision <= PrecisionType{0}) {
            error("Precision must be positive");
            precision = new_precision;
        }
    }

    void reset_count() { count = 100; }
    void reset_xscale() { xscale = 25; }
    void reset_yscale() { yscale = 25; }

private:
    std::function<double(double)> f;
    double r1;
    double r2;
    Point orig;
    int count;
    double xscale;
    double yscale;
    double precision;
};

// Ex 4: graph some functions with axes and labels
void more_graphing() {
    Application app;
    Simple_window win({50, 50}, 600, 600, "Function graphs");

    constexpr int xmax = 600;   // Window size
    constexpr int ymax = 600;

    constexpr int xlength = xmax*2/3;
    constexpr int ylength = ymax*2/3;

    constexpr int xoffset = xmax*1/6;
    constexpr int yoffset = ymax*1/6;

    constexpr int yspace = ymax - (ymax*1/6);

    constexpr int xscale = 20;
    constexpr int yscale = 20;

    constexpr double r_min = -10;
    constexpr double r_max = 10;

    constexpr Point orig{xmax/2, ymax/2};

    constexpr int n_points = 400;

    Axis x {Axis::x, Point{xoffset, ymax/2}, xlength, xlength/xscale, "1 notch == 20 pixels" };
    win.attach(x);
    x.label.move(200,200);

    Axis y {Axis::y, Point{xmax/2, yspace}, ylength, ylength/yscale, "" };
    win.attach(y);

    Function f0 { [](double x) { return sin(x); }, r_min, r_max, orig, n_points, xscale, yscale };
    f0.set_color(Color::blue);
    win.attach(f0);
    Text f0_label{ Point{xoffset, yoffset}, "sin(x)" };
    f0_label.set_color(Color::blue);
    win.attach(f0_label);


    Function f1 { [](double x) { return cos(x); }, r_min, r_max, orig, n_points, xscale, yscale };
    f1.set_color(Color::red);
    win.attach(f1);
    Text f1_label{ Point{xoffset, yoffset + 20}, "cos(x)" };
    f1_label.set_color(Color::red);
    win.attach(f1_label);


    Function f2 { [](double x) { return sin(x) + cos(x); }, r_min, r_max, orig, n_points, xscale, yscale };
    f2.set_color(Color::green);
    win.attach(f2);
    Text f2_label{ Point{xoffset, yoffset + 40}, "sin(x) + cos(x)" };
    f2_label.set_color(Color::green);
    win.attach(f2_label);


    Function f3 { [](double x) { return (sin(x)*sin(x)) + (cos(x)*cos(x)); }, r_min, r_max, orig, n_points, xscale, yscale };
    f3.set_color(Color::dark_magenta);
    win.attach(f3);
    Text f3_label{Point{xoffset, yoffset + 60}, "sin(x)^2 + cos(x)^2"};
    f3_label.set_color(Color::dark_magenta);
    win.attach(f3_label);

    win.wait_for_button();
}

// Ex 5: animate the Leibniz series approximation to pi/4
double leibniz_series(int n) {
    double sum = 0;
    for (int i=0; i<=n; ++i)
        sum += pow(-1,i)*(1.0/(2*i+1));
    return sum;
}

double recursive_leibniz(double n) {
    if (n==0)
        return 1.0;
    else {
        return recursive_leibniz(n-1) + pow(-1,n)*(1.0/(2*n+1));
    }
}

void animate_leibniz() {
    Application app;
    Simple_window win({50, 50}, 600, 600, "Function graphs");

    constexpr int xmax = 600;   // Window size
    constexpr int ymax = 600;

    constexpr int xlength = xmax*2/3;
    constexpr int ylength = ymax*2/3;

    constexpr int xoffset = xmax*1/6;

    constexpr int yspace = ymax - (ymax*1/6);

    constexpr int xscale = 40;
    constexpr int yscale = 40;

    constexpr double r_min = -10;
    constexpr double r_max = 10;

    constexpr Point orig{xmax/2, ymax/2};

    Axis x {Axis::x, Point{xoffset, ymax/2}, xlength, xlength/xscale, "1 notch == 10 pixels" };
    win.attach(x);
    x.label.move(200,200);

    Axis y {Axis::y, Point{xmax/2, yspace}, ylength, ylength/yscale, "" };
    win.attach(y);

    Function pi_4 { [](double) { return M_PI_4; }, r_min, r_max, orig, xlength/xscale, xscale, yscale };
    pi_4.set_color(Color::blue);
    win.attach(pi_4);

    for (int i=0; i<20; ++i) {
        Function leibniz { [i](double) {
                             return leibniz_series(i); },
                         r_min, r_max, orig, 400, xscale, yscale };
        win.attach(leibniz);
        win.wait_for_button();
        win.detach(leibniz);
    }

    win.wait_for_button();
}

// Ex 6: Design and implement a bar graph class
// Ex 7: add colors and labels to class
class Bar_graph {
public:
    Bar_graph(const vector<double>& data, Simple_window& win,
              Point origin = Point{100, 300},
              int x_scale = 20,
              int y_scale = 20,
              Color color = Color::white,
              string title = "",
              Vector<string> labels = {})
        : data_{data},
        win_{win},
        orig_{origin},
        xscale_{x_scale},
        yscale_{y_scale},
        color_{color},
        labels_{labels},
        xlength_{xscale_ * (2 * static_cast<int>(data_.size()) + 1)},
        max_data_{*max_element(data_.begin(), data_.end())},
        ylength_{static_cast<int>((max_data_ + 1) * yscale_)},
        x_axis_{Axis::x, orig_, xlength_, 0, title},
        y_axis_{Axis::y, orig_, ylength_, ylength_/yscale_, ""}
    {
        draw();
    }

    void set_color(Color clr) {
        for (int i=0; i<static_cast<int>(bars_.size()); ++i) {
            bars_[i].set_fill_color(clr);
            win_.attach(bars_[bars_.size()-1]);
        }
    }

private:
    const vector<double>& data_;
    Simple_window& win_;
    Point orig_;
    int xscale_;
    int yscale_;
    Color color_;
    Vector<string> labels_;
    int xlength_;
    double max_data_;
    int ylength_;
    Vector_ref<Rectangle> bars_;
    Vector_ref<Text> text_;
    Axis x_axis_;
    Axis y_axis_;

    void draw() {
        win_.attach(x_axis_);
        x_axis_.label.move(xlength_ - orig_.x + xscale_, - ylength_ - (yscale_*2));
        win_.attach(y_axis_);

        for (int i = 0; i < static_cast<int>(data_.size()); ++i) {
            int r_height = static_cast<int>(data_[i] * yscale_);
            bars_.push_back(make_unique<Rectangle>(
                Point{orig_.x + (2*i+1)*xscale_,
                      orig_.y - r_height},
                xscale_,
                r_height
                ));
            text_.push_back(make_unique<Text>( Point{orig_.x + (2*i+1)*xscale_,orig_.y}, labels_[i]));

            bars_[i].set_fill_color(color_);

            win_.attach(bars_[bars_.size()-1]);
            win_.attach(text_[text_.size()-1]);
        }
    }
};

void display_bar_graph() {
    Application app;
    Simple_window win({50, 50}, 600, 600, "Function graphs");

    vector<double> data{5.5, 3.2, 1.0, 7.8};
    Bar_graph graph{data, win, Point{100,300}, 20, 20, Color::blue, "My graph", {"First", "Second", "Third", "Fourth"}};
    win.wait_for_button();
}

int main(int /*argc*/, char * /*argv*/[])
{
    display_bar_graph();
}
