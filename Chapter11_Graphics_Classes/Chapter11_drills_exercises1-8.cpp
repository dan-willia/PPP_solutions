#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

void Chapter11_drills() {
    Application app;
    Simple_window win{Point{50,50},800,1000,"Chapter 11 drill"};

    int x_size = 800;
    int y_size = 800;
    int x_grid = 100;
    int y_grid = 100;

    Lines grid;
    for (int x=x_grid; x<x_size; x+=x_grid)
        grid.add(Point{x,0},Point{x,y_size});
    for (int y=y_grid; y<=y_size; y+=y_grid)
        grid.add(Point{0,y},Point{x_size,y});

    win.attach(grid);

    Vector_ref<Rectangle> vr;

    for (int i=0; i<8; ++i) {
        vr.push_back(make_unique<Rectangle>(Point{i*x_grid,i*x_grid}, x_grid, y_grid));
        vr[vr.size()-1].set_fill_color(Color::red);
        win.attach(vr[vr.size()-1]);
    }

    Image copter{Point{0,200}, "/Users/daniel/Desktop/Misc_Courses/C++/Part_2/ProgrammingPrinciplesAndPracticeUsingQt/copter.jpg"};
    copter.scale(200,200,false);
    win.attach(copter);

    Image copter2{Point{200,0}, "/Users/daniel/Desktop/Misc_Courses/C++/Part_2/ProgrammingPrinciplesAndPracticeUsingQt/copter.jpg"};
    copter2.scale(200,200,false);
    win.attach(copter2);

    Image copter3{Point{400,200}, "/Users/daniel/Desktop/Misc_Courses/C++/Part_2/ProgrammingPrinciplesAndPracticeUsingQt/copter.jpg"};
    copter3.scale(200,200,false);
    win.attach(copter3);

    Image copter4{Point{600,500}, "/Users/daniel/Desktop/Misc_Courses/C++/Part_2/ProgrammingPrinciplesAndPracticeUsingQt/copter.jpg"};
    copter4.scale(100,100,false);
    win.attach(copter4);

    for (int i=0; i<3; ++i) {
        win.wait_for_button();
        copter4.move(-100,0);
    }
}


// Ex 1: create an Arrow class
struct Arrow : Shape {
    Arrow(Point begin_, Point end_)
        : l{begin_, end_}
    {
        const int tri_b = 12; // Base width of the arrowhead
        const int tri_h = 16; // Height of the arrowhead

        // Calculate the angle of the line
        double dx = end_.x - begin_.x;
        double dy = end_.y - begin_.y;
        double theta = atan2(dy, dx);

        // Arrowhead vertices
        Point tip = end_;
        Point base1{
            static_cast<int>(end_.x - cos(theta) * tri_h + cos(theta + M_PI_2) * tri_b / 2),
            static_cast<int>(end_.y - sin(theta) * tri_h + sin(theta + M_PI_2) * tri_b / 2)
        };
        Point base2{
            static_cast<int>(end_.x - cos(theta) * tri_h + cos(theta - M_PI_2) * tri_b / 2),
            static_cast<int>(end_.y - sin(theta) * tri_h + sin(theta - M_PI_2) * tri_b / 2)
        };

        // Create the arrowhead polygon
        tri.add(tip);
        tri.add(base1);
        tri.add(base2);
        tri.set_fill_color(Color::black);
    }

    void draw_specifics(Painter& painter) const override {
        l.draw(painter); // Draw the line
        tri.draw(painter); // Draw the arrowhead
    }

private:
    Line l;
    Polygon tri;
};

void display_arrows() {
    Application app;
    Simple_window win{Point{50,50}, 1000, 1000, "Ex 1"};

    Arrow a{Point{50,50}, Point{100,100}};
    win.wait_for_button();
}

// Ex 2: write functions that return the "connection points" of a Rectangle
Point nw(const Rectangle& r) {
    return r.point(0);
}

Point sw(const Rectangle& r) {
    return {r.point(0).x, r.point(0).y + r.height()};
}

Point ne(const Rectangle& r) {
    return {r.point(0).x + r.width(), r.point(0).y};
}

Point se(const Rectangle& r) {
    return {r.point(0).x + r.width(), r.point(0).y + r.height()};
}

Point n(const Rectangle& r) {
    return {r.point(0).x + r.width()/2, r.point(0).y};
}

Point s(const Rectangle& r) {
    return {r.point(0).x + r.width()/2, r.point(0).y + r.height()};
}

Point e(const Rectangle& r) {
    return {r.point(0).x + r.width(), r.point(0).y + r.height()/2};
}

Point w(const Rectangle& r) {
    return {r.point(0).x, r.point(0).y + r.height()/2};
}

Point center(const Rectangle& r) {
    return {r.point(0).x + r.width()/2, r.point(0).y + r.height()/2};
}

void display_connection_pts() {
    Application app;

    const int win_w = 1200;
    const int win_h = 600;
    Simple_window win{Point{50,50}, win_w, win_h, "Chapter 11 exercise 1"};

    Rectangle r{{50,50}, 400, 400};
    win.attach(r);

    Point northeast = ne(r);
    Mark mne{northeast, 'x'};
    win.attach(mne);

    Point southeast = se(r);
    Mark mse{southeast, 'x'};
    win.attach(mse);

    Point northwest = nw(r);
    Mark mnw{northwest, 'x'};
    win.attach(mnw);

    Point southwest = sw(r);
    Mark msw{southwest, 'x'};
    win.attach(msw);

    Point north = n(r);
    Mark mn{north, 'x'};
    win.attach(mn);

    Point south = s(r);
    Mark ms{south, 'x'};
    win.attach(ms);

    Point east = e(r);
    Mark me{east, 'x'};
    win.attach(me);

    Point west = w(r);
    Mark mw{west, 'x'};
    win.attach(mw);

    Point center_r = center(r);
    Mark mc{center_r, 'x'};
    win.attach(mc);

    win.wait_for_button();
}

// Ex 3: Circle connection points
Point center(const Circle& c) {
    return c.center();
}

Point nw(const Circle& c) {
    return {c.center().x - c.radius(), c.center().y - c.radius()};
}

Point n(const Circle& c) {
    return {c.center().x, c.center().y - c.radius()};
}

Point ne(const Circle& c) {
    return {c.center().x + c.radius(), c.center().y - c.radius()};
}

Point w(const Circle& c) {
    return {c.center().x - c.radius(), c.center().y};
}

Point e(const Circle& c) {
    return {c.center().x + c.radius(), c.center().y};
}

Point sw(const Circle& c) {
    return {c.center().x - c.radius(), c.center().y + c.radius()};
}

Point s(const Circle& c) {
    return {c.center().x, c.center().y + c.radius()};
}

Point se(const Circle& c) {
    return {c.center().x + c.radius(), c.center().y + c.radius()};
}

// Ex 3 (cont): Ellipse connection points

Point nw(const Ellipse& el) {
    return el.point(0);
}

Point n(const Ellipse& el) {
    return {el.point(0).x + el.major(), el.point(0).y};
}

Point ne(const Ellipse& el) {
    return {el.point(0).x + el.major()*2, el.point(0).y};
}

Point w(const Ellipse& el) {
    return {el.point(0).x, el.point(0).y + el.minor()};
}

Point center(const Ellipse& el) {
    return el.center();
}

Point e(const Ellipse& el) {
    return {el.center().x + el.major(), el.center().y};
}

Point sw(const Ellipse& el) {
    return {el.point(0).x, el.center().y + el.minor()};
}

Point s(const Ellipse& el) {
    return {el.center().x, el.center().y + el.minor()};
}

Point se(const Ellipse& el) {
    return {el.center().x + el.major(), el.center().y + el.minor()};
}

// Ex 4: recreate class diagram from 10.6
struct Box : Shape {
    Box(Point xy, int w, int h, string message)
        : r{xy, w, h}, t{{center(r).x - int(message.length() * 4), center(r).y - 8}, message}
    {
        r.set_fill_color(Color::cyan);
    }

    void set_rect_fill(Color c) {
        r.set_fill_color(c);
    }

    const Rectangle& rect() const { return this->r; }
    const Text& text() const { return this->t; }

    void draw_specifics(Painter& painter) const override {
        r.draw(painter);
        t.draw(painter);
    }

private:
    Rectangle r;
    Text t;
};

void display_class_diagram() {
    Application app;

    const int win_w = 1200;
    const int win_h = 600;
    Simple_window win{Point{50,50}, win_w, win_h, "Ex 4"};

    const int base = 50;
    const int box_x = 150;
    const int box_y = 50;

    Box b1({base, base}, box_x, box_y, "Window");
    win.attach(b1);

    Box b2({base, base*3}, box_x, box_y, "Simple_window");
    win.attach(b2);

    Arrow ab2b1{n(b2.rect()), s(b1.rect())};
    win.attach(ab2b1);

    Box b3({base*6, base}, box_x, box_y, "Line_style");
    win.attach(b3);

    Box b4({base*6, base*3}, box_x, box_y, "Shape");
    win.attach(b4);

    Arrow ab3b4{n(b4.rect()), s(b3.rect())};
    win.attach(ab3b4);

    Box b5({base*11, base}, box_x, box_y, "Color");
    win.attach(b5);

    Box b6({base*11, base*3}, box_x, box_y, "Point");
    win.attach(b6);

    Arrow ab5b6{n(b6.rect()), s(b5.rect())};
    win.attach(ab5b6);

    const int box_x2 = box_x-50;
    const int width = 15;

    Box b7{ {base - base/2, base*6}, box_x-50, box_y, "" };
    win.attach(b7);

    Box b8{ {ne(b7.rect()).x + width, ne(b7.rect()).y}, box_x2, box_y, "Lines" };
    win.attach(b8);

    Box b9{ {ne(b8.rect()).x + width, ne(b8.rect()).y}, box_x2, box_y, "Polygon" };
    win.attach(b9);

    Box b10{ {ne(b9.rect()).x + width, ne(b9.rect()).y}, box_x2, box_y, "Axis" };
    win.attach(b10);

    Box b11{ {ne(b10.rect()).x + width, ne(b10.rect()).y}, box_x2, box_y, "Rectangle" };
    win.attach(b11);

    Box b12{ {ne(b11.rect()).x + width, ne(b11.rect()).y}, box_x2, box_y, "Text" };
    win.attach(b12);

    Box b13{ {ne(b12.rect()).x + width, ne(b12.rect()).y}, box_x2, box_y, "Image" };
    win.attach(b13);

    Arrow ab7b4{n(b7.rect()), s(b4.rect())};
    win.attach(ab7b4);

    Arrow ab8b4{n(b8.rect()), s(b4.rect())};
    win.attach(ab8b4);

    Arrow ab9b4{n(b9.rect()), s(b4.rect())};
    win.attach(ab9b4);

    Arrow ab10b4{n(b10.rect()), s(b4.rect())};
    win.attach(ab10b4);

    Arrow ab11b4{n(b11.rect()), s(b4.rect())};
    win.attach(ab11b4);

    Arrow ab12b4{n(b12.rect()), s(b4.rect())};
    win.attach(ab12b4);

    Arrow ab13b4{n(b13.rect()), s(b4.rect())};
    win.attach(ab13b4);

    win.wait_for_button();
}

// Ex 5: make an rgb color chart
void rgb_color_chart() {
    Application app;

    const int win_w = 1400;
    const int win_h = 800;
    Simple_window win{Point{50,50}, win_w, win_h, "Chapter 11 exercise 1"};

    Vector_ref<Rectangle> vr;

    const int max = 256;
    const int side = 2;
    const int top = 2;
    const int left = 2;
    int r = 0;
    int g = 0;
    int b = 0;

    for (int i=0; i<max; ++i) {     // rows
        for (int j=0; j<max; ++j) { // columns
            vr.push_back(make_unique<Rectangle>(Point{i*side + top, j*side + left}, side, side));
            vr[vr.size()-1].set_fill_color(Color(r,g,b));
            g = (g+1) % 256;
            win.attach(vr[vr.size()-1]);
        }
        r++;
    }

    win.wait_for_button();
}

// Ex 6: define a class Regular_hexagon
struct Regular_hexagon : Closed_polyline {
    Regular_hexagon(Point center, int d_to_corner)
        : c{center}, d{d_to_corner}
    {
        // Calculate and add points of the hexagon
        Point p1{c.x + d, c.y};
        Point p2{c.x + d/2, c.y - int(d*sqrt(3)/(2.0))};
        Point p3{c.x - d/2, c.y - int(d*sqrt(3)/(2.0))};
        Point p4{c.x - d, c.y};
        Point p5{c.x - d/2, c.y + int(d*sqrt(3)/(2.0))};
        Point p6{c.x + d/2, c.y + int(d*sqrt(3)/(2.0))};

        add(p1); add(p2); add(p3); add(p4); add(p5); add(p6);
    }

    void draw_specifics(Painter& painter) const override {
        Closed_polyline::draw_specifics(painter);   // use parent's draw functionality
    }

    Point center() const { return c; }
    int get_d() const { return d; }

private:
    Point c;    // center of hexagon
    int d;      // distance to vertex
};

void display_regular_hexagon() {
    Application app;

    const int win_w = 1400;
    const int win_h = 800;
    Simple_window win{Point{50,50}, win_w, win_h, "Chapter 11 exercise 1"};

    Regular_hexagon r( Point{500,500}, 100);
    win.attach(r);

    Mark m{Point{500,500}, 'x'};
    win.attach(m);

    win.wait_for_button();
}

// Ex 7: tile part of window with regular hexagons
void hex_tile() {
    Application app;
    Simple_window win{Point{50,50}, 600, 400, "Ex 7"};

    constexpr int d = 26;
    constexpr int x = 100;
    constexpr int y = 100;

    Regular_hexagon hex1{Point{100,100}, d};
    hex1.set_fill_color(Color::red);
    win.attach(hex1);

    Vector_ref<Regular_hexagon> vh;
    for (int i=1; i<7; ++i) {
        vh.push_back(make_unique<Regular_hexagon>(Point{ x + static_cast<int>(d*sqrt(3) * cos(i*M_PI/3 + M_PI/6)),
                                                        y + static_cast<int>(d*sqrt(3) * sin(i*M_PI/3 + M_PI/6))},
                                                  d));
        win.attach(vh[vh.size()-1]);
    }

    constexpr int x2 = 100 + 3*d;

    Regular_hexagon hex2{Point{x2,y}, d};
    hex2.set_fill_color(Color::red);
    win.attach(hex2);

    Vector_ref<Regular_hexagon> vh2;
    for (int i=1; i<7; ++i) {
        vh.push_back(make_unique<Regular_hexagon>(Point{ x2 + static_cast<int>(d*sqrt(3) * cos(i*M_PI/3 + M_PI/6)),
                                                        y + static_cast<int>(d*sqrt(3) * sin(i*M_PI/3 + M_PI/6))},
                                                  d));
        win.attach(vh[vh.size()-1]);
    }

    win.wait_for_button();
}

// Ex 8: define a class Regular_polygon
struct Regular_polygon : Closed_polyline {
    Regular_polygon(Point center, int sides, int distance_to_corner)
        : c{center}, s{sides}, d{distance_to_corner}
    {
        if (sides < 2)
            error("Regular polygon must have > 2 sides");

        for (int i=0; i<sides; ++i) {
            add(Point{ c.x + static_cast<int>(d*sqrt(3) * cos(i*2*M_PI/s)),
                      c.y + static_cast<int>(d*sqrt(3) * sin(i*2*M_PI/s))});
        }
    }

    void draw_specifics(Painter& painter) const override {
        Closed_polyline::draw_specifics(painter);
    }

private:
    Point c;    // center
    int s;      // number of sides
    int d;      // distance to a corner
};

void display_regular_polygons(int max_sides) {
    Application app;
    Simple_window win{Point{50,50}, 1000, 1000, "Ex 7"};

    constexpr int x = 500;
    constexpr int y = 500;
    constexpr int d = 100;

    Vector_ref<Regular_polygon> rp;
    for (int i=3; i<max_sides; ++i) {
        rp.push_back(make_unique<Regular_polygon>( Point{x, y}, i, d));
        win.attach(rp[rp.size()-1]);
        win.wait_for_button();
    }

    Text t{ Point{50,50}, "Last"};
    win.attach(t);
    win.wait_for_button();
}

int main() {
    Chapter11_drills();
    display_arrows();           // Ex 1
    display_connection_pts();   // Ex 2
                                // See class definitions for Ex 3
    display_class_diagram();    // Ex 4 
    rgb_color_chart();          // Ex 5
    display_regular_hexagon();  // Ex 6
    hex_tile();                 // Ex 7
    display_regular_polygons(); // Ex 8

}
