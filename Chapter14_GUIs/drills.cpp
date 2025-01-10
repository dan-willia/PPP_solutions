#include "PPP/Graph.h"
#include "PPP/Window.h"
#include "PPP/GUI.h"

using namespace Graph_lib;

struct Lines_window : Window {
    Lines_window(Application& application, Point xy, int w, int h, const string& title);
    Open_polyline lines;
    void wait_for_button();

private:
    Application* app = nullptr;
    Button quit_button;             // a Widget
    In_box next_xy;                 // a Widget
    Out_box xy_out;                 // a Shape
    void next();
    void quit();
};

Lines_window::Lines_window(Application& application, Point xy, int w, int h, const string& title)
    : Window{ xy, w, h, title },
    app(&application),
    quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", [this]() { quit(); }},
    next_xy{ Point{250,0}, 50, 20, "next xy:", [this]() { next(); }},
    xy_out{ Point{10,10}, "current (x,y): "}
{
    attach(lines);
    attach(quit_button);

    next_xy.hide_buttons();     // a Qt input box comes with buttons; hide them
    attach(next_xy);
    next_xy.show();             // show the box itself

    xy_out.label.set_font_size(8);  // use a smaller than default font
    xy_out.data.set_font_size(8);
    attach(xy_out);
}

void Lines_window::quit()
{
    end_button_wait();      // don't wait anymore
    next_xy.dismiss();      // clean up
    app->quit();
}

void Lines_window::next()   // the action performed by next_xy when woken up
{
    if (next_xy.last_result() == In_box::accepted) {    // check if the value has changed
        string s = next_xy.last_string_value();     // read coordinate pair
        istringstream iss { s };
        int x = 0;
        char ch = 0;
        int y = 0;
        iss >> x >> ch >> y;
        lines.add(Point{ x,y });

        ostringstream oss;          // update current position readout
        oss << '(' << x << ',' << y << ')';
        xy_out.put(oss.str());

    }
    next_xy.clear_last_result();    // clear the box
}

struct Color_window : Lines_window {
    Color_window(Application& app, Point xy, int w, int h, const string& title);
    void change(Color c) { lines.set_color(c); }
    void change_style(Line_style ls) { lines.set_style(ls); }
private:
    void hide_menu() { color_menu.hide(); menu_button.show(); }

    Button menu_button;
    Menu color_menu;
    Menu styles_menu;
};

Color_window::Color_window(Application& app, Point xy, int w, int h, const string& title)
    : Lines_window{ app, xy, w, h, title },
    menu_button{ Point{x_max() - 95, 30}, 80, 20, "color menu",
                  [&] { menu_button.hide(); color_menu.show();} },
    color_menu{ Point{x_max() - 70, 40}, 70, 30, Menu::vertical, "color" },
    styles_menu{ Point{x_max() - 80, 140}, 80, 30, Menu::vertical, "line styles" }
{
    attach(color_menu);
    color_menu.attach(make_unique<Button>( Point{0,0}, 0,0, "red",
                                          [&]{ change(Color::red); hide_menu(); }));
    color_menu.attach(make_unique<Button>( Point{0,0}, 0,0, "blue",
                                          [&]{ change(Color::blue); hide_menu(); }));
    color_menu.attach(make_unique<Button>( Point{0,0}, 0,0, "black",
                                          [&]{ change(Color::black); hide_menu(); }));
    attach(menu_button);
    hide_menu();

    styles_menu.attach(make_unique<Button>( Point{0,0}, 0,0, "solid",
                                           [&]{ change_style(Line_style::solid); }));
    styles_menu.attach(make_unique<Button>( Point{0,0}, 0,0, "dash",
                                           [&]{ change_style(Line_style::dash); }));
    styles_menu.attach(make_unique<Button>( Point{0,0}, 0,0, "dot",
                                           [&]{ change_style(Line_style::dot); }));
    styles_menu.attach(make_unique<Button>( Point{0,0}, 0,0, "dashdot",
                                           [&]{ change_style(Line_style::dashdot); }));
    styles_menu.attach(make_unique<Button>( Point{0,0}, 0,0, "dashdotdot",
                                           [&]{ change_style(Line_style::dashdotdot); }));
    attach(styles_menu);
}

int main()
try
{
    Application app;
    Color_window win{app, Point{100,100}, 600, 400, "lines"};
    app.gui_main();
}
catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "Some exception\n";
    return 2;
}
