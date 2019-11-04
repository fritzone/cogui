#include "cogui.h"
#include "loguru.h"

int main( int argc, char* argv[] )
{
    cogui::init(argc, argv);

    using namespace cogui;

    auto a = cogui::window(5, 5, 70, 15, L"A window with title",
                           window::on_resize = [](window* win, int w,int h){info() << "(lambda slot) new size:" << w << "x" << h;},
                           window::on_close  = [](window* w){info() << "Closing this window"; },
                           window::on_mouse_down = [](window* w, cogui::mouse::button b, int x, int y){info() << "Mouse (" << mouse::get().buttonName(b) << ") down:" << x << ", " << y; },
                           window::on_mouse_up = [](window* w, cogui::mouse::button b, int x, int y){info() << "Mouse (" << mouse::get().buttonName(b) << ") up:" << x << ", " << y; }
    );

    auto& b = a.add_button(5,5, 10, 2, L"Vertical layout",
                           button::on_click = [&a](button*){info() << "Thanks";
                                a.setLayout<cogui::layout::vertical>();
                                a.redraw();
                           }
    );

    auto& c = a.add_button(35,5, 20, 2, L"Horizontal layout",
                           button::on_click = [&a](button*){info() << "Thanks";
                                a.setLayout<cogui::layout::horizontal>().expand(1);
                                a.redraw();
                           }
    );
    auto& d = a.add_button(35,5, 5, 2, L"Grid layout",
                           button::on_click = [&a](button*){info() << "Thanks";
                                a.setLayout<cogui::layout::grid>(2, 2);
                                a.redraw();
                           }
    );

    auto& e = a.add_button(35,5, 5, 2, L"B");
    auto& f = a.add_button(35,5, 5, 2, L"C");

    miso::connect(&a, a.sig_on_resize, [](window* win, int w, int h){info() << "(slot) new size:" << w << "x" << h;});
    miso::connect(&c, c.sig_on_click, [](button*){ info() << "You clicked me...:" ;});

    a.setLayout<cogui::layout::grid>(3, 3);

    cogui::application app;
    app.run();

}
