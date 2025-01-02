#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

struct Smiley : Circle {
    Smiley(Point c, int r)
        : Circle(c, r),
        // face{c, r},
        left_eye {Point {c.x - r/2, c.y - r/2}, r/5},
        right_eye {Point {c.x + r/2, c.y - r/2}, r/5},
        mouth { {c.x, c.y + r/4}, r/2, r/2, 180, 180}
    {}

    void draw_specifics(Painter& painter) const override {
        // face.draw(painter);
        left_eye.draw(painter);
        right_eye.draw(painter);
        mouth.draw(painter);
    }

private:
    // Circle face;
    Circle left_eye;
    Circle right_eye;
    Arc mouth;
};

class Frowny : public Circle {
public:
    Frowny(Point c, int r)
        : Circle(c, r),
          left_eye {Point {c.x - r/2, c.y - r/2}, r/5},
          right_eye {Point {c.x + r/2, c.y - r/2}, r/5},
          mouth { {c.x, c.y + r/4}, r/2, r/2, 0, 180}
    {}

    void draw_specifics(Painter& painter) const override {
        left_eye.draw(painter);
        right_eye.draw(painter);
        mouth.draw(painter);
    }

private:
    Circle left_eye;
    Circle right_eye;
    Arc mouth;
};

void display_smiley_frowney() {
    Application app;
    Simple_window win({20, 20}, 600, 400, "Main window");

    int radius = 50;
    Point center{150,150};

    Circle face {center, radius};
    win.attach(face);

    Circle left_eye {Point{center.x - radius/2, center.y - radius/2}, 10};
    win.attach(left_eye);

    Circle right_eye {Point{center.x + radius/2, center.y - radius/2}, 10};
    win.attach(right_eye);

    Arc mouth { {center.x, center.y + radius/4}, radius/3, radius/3, 180, 180};
    win.attach(mouth);

    Smiley sm{Point{300,100}, 10};
    win.attach(sm);

    Frowny fr{Point{300,300}, 50};
    win.attach(fr);

    Smiley sm2{Point{500,300}, 50};
    win.attach(sm2);

    win.wait_for_button();
}

class AbstractClass {
public:
    virtual void func() =0;     // pure virtual function, so it is an abstract class
};

class AbstractClass2 {
public:
    int get_x() { return x; }
    int get_y() { return y; }
protected:
    AbstractClass2(int xx, int yy) : x{xx}, y{yy} {}    // constructor is protected
                                                        // so can only be used by derived
                                                        // classes
private:
    int x;
    int y;
};

struct Immobile_Circle : Shape {
    Immobile_Circle(Point p, int rr)	// center and radius
        :r{ rr } {
        add(Point{ p.x - r, p.y - r });
    }

    void move(int dx, int dy) override {
        (void)dx;
        (void)dy;
        error("Immobile circle cannot be moved");
    }

    void draw_specifics(Painter& painter) const override {
        painter.draw_ellipse(center(), r, r);
    }

    Point center() const { return { point(0).x + r, point(0).y + r }; }

    void set_radius(int rr) { r=rr; redraw();}
    int radius() const { return r; }
private:
    int r;
};

void move_immobile_circle() {
    Application app;
    Simple_window win({20, 20}, 600, 400, "Main window");

    Circle c{Point{100,100}, 50};
    win.attach(c);

    Immobile_Circle im{Point{100,200}, 50};
    win.attach(im);

    win.wait_for_button();

    c.move(25, 25);
    im.move(25,25);

    win.wait_for_button();
}

struct Striped_rectangle : Rectangle {
    Striped_rectangle(Point p, int w, int h, Color clr)
        : Rectangle{ p, w, h }
    {
        for (int i=p.y+1; i<h+p.y; i+=2) {
            ls.add( Point{p.x + 1, i}, Point{p.x - 1 + w, i} );
        }
        ls.set_color(clr);
    }

    void draw_specifics(Painter& painter) const override {
        Rectangle::draw_specifics(painter);
        ls.draw(painter);
    }

    const Lines& lines() const { return ls; }
    void set_stripe_color(Color c) {
        ls.set_color(c);
        redraw();
    }

private:
    Lines ls;
};

void display_striped_rectangle() {
    Application app;
    Simple_window win({20, 20}, 600, 400, "Main window");

    int width = 100;
    int height = 200;
    Rectangle r{Point{50,50}, width, height};

    Lines ls;
    for (int i=51; i<height+50; i+=2) {
        ls.add(Point{50+1, i}, Point{50 - 1 + width, i});
    }
    ls.set_color(Color::green);

    win.attach(r);
    win.attach(ls);

    Striped_rectangle sr{Point{150,50}, height, width, Color::blue};
    win.attach(sr);

    win.wait_for_button();

    sr.set_stripe_color(Color::dark_magenta);
    win.wait_for_button();

    sr.set_stripe_color(Color::black);
    win.wait_for_button();
}

int main(int /*argc*/, char * /*argv*/[])
{
    display_striped_rectangle();
}
