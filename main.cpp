#include "cogui.h"
#include "loguru.h"

#include <iostream>

int main( int argc, char* argv[] )
{

    std::wstring t = std::wstring(L"Raise your \U0001F450");
    std::cout << t.length() << " " << t.size() << " " << wcslen(t.c_str()) <<  std::endl;


    cogui::init(argc, argv);

    using namespace cogui;

    auto a = cogui::window(5, 5, 70, 15, t,
                           window::on_resize = [](window* win, int w,int h){info() << "(lambda slot) new size:" << w << "x" << h;},
                           window::on_close  = [](window* w){info() << "Closing this window"; },
                           window::on_mouse_down = [](window* w, cogui::mouse::button b, int x, int y){info() << "Mouse (" << mouse::get().buttonName(b) << ") down:" << x << ", " << y; },
                           window::on_mouse_up = [](window* w, cogui::mouse::button b, int x, int y){info() << "Mouse (" << mouse::get().buttonName(b) << ") up:" << x << ", " << y; },
                           window::sysmenu = menu{
                               {L"select", action::on_trigger = [](action*){}},
                               {L"No select", action::on_trigger = [](action*){}}
                           }
    );

    auto& b = a.add_button(5,5, 10, 2, L"&Vertical layout",
                           button::on_click = [&a](button*){info() << "Thanks";
                                a.setLayout<cogui::layout::vertical>().expand(2);
                                a.redraw();
                           }
    );

    auto& c = a.add_button(35,5, 20, 2, L"&Horizontal layout",
                           button::on_click = [&a](button*){info() << "Thanks";
                                a.setLayout<cogui::layout::horizontal>().expand(1);
                                a.redraw();
                           }
    );
    auto& d = a.add_button(35,5, 5, 2, L"G&rid layout",
                           button::on_click = [&a](button*){info() << "Thanks";
                                a.setLayout<cogui::layout::grid>(2, 2);
                                a.redraw();
                           }
    );

    auto& e = a.add_button(35,5, 5, 2, L"B");
    auto& f = a.add_button(35,5, 5, 2, L"C");
    auto& g = a.add_button(35,5, 5, 2, L"D");
    auto& h = a.add_button(35,5, 5, 2, L"E");

    miso::connect(&a, a.sig_on_resize, [](window* win, int w, int h){info() << "(slot) new size:" << w << "x" << h;});
    miso::connect(&c, c.sig_on_click, [](button*){ info() << "You clicked me...:" ;});

    a.setLayout<cogui::layout::grid>(3, 3);

    cogui::application app;
    app.run();

}
