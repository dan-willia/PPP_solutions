#include "PPP/Graph.h"
#include "PPP/Window.h"
#include "PPP/GUI.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

// Ex 1: Create a My_window which is a Simple_window with a quit button
struct My_window : Simple_window {
    My_window(Point xy, int w, int h, const string& title);
    ~My_window();
private:
    Button quit_button;
};

My_window::My_window(Point xy, int w, int h, const string& title)
    : Simple_window(xy, w, h, title)
    , quit_button{Point{w - 70, 25}, 70, 20, "Quit", [this]() { close(); }}
{
    attach(quit_button);
}

My_window::~My_window() {}

void display_My_window() {
    Application app;
    My_window win{Point{400,400}, 600, 400, "simple_window2"};

    Rectangle r{Point{100,100}, 100, 200};
    win.attach(r);

    win.wait_for_button();

    r.set_fill_color(Color::blue);

    win.wait_for_button();
}

// Ex 2: Create a My_window with 4x4 checkerboard of square buttons; do an action when button is pressed

struct Checkerboard : My_window {
    Checkerboard(Point xy, int side, const string& title);  // side is the length of entire side of CB
    ~Checkerboard();
    void hide_button(int b);            // b is the index of button [0,16)
    void which_square(int b);
private:
    Vector_ref<Button> squares;
    Out_box coordinates;
};

Checkerboard::Checkerboard(Point xy, int side, const string& title)
    : My_window{xy, side + 100, side + 100, title}  // make entire window bigger than CB
    , coordinates{Point{0,10}, "which square: "}
{
    int sq_side = side/4;
    for (int y=50; y<side + 50; y+=sq_side) {
        for (int x=50; x<side + 50; x+=sq_side) {
            squares.push_back(make_unique<Button>(Point{x,y},
                                                  sq_side, sq_side, "",
                                                  [b = squares.size(), this]() { hide_button(b); which_square(b); } )); // callback for buttons
            attach(squares[squares.size()-1]);
        }
    }
    attach(coordinates);
}

void Checkerboard::hide_button(int b) {     // b is the index of button [0,16)
    for (auto sq : squares) {
        sq->show();
    }
    squares[b].hide();
}

void Checkerboard::which_square(int b) {
    coordinates.put(b);
}

Checkerboard::~Checkerboard() {}

void display_checkboard() {
    Application app;
    Checkerboard cb{Point{50,50}, 800, "Checkers test"};

    cb.wait_for_button();
}

int main()
try
{
    display_My_window();
    display_checkboard();
}
catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "Some exception\n";
    return 2;
}
