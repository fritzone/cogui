#include "cogui.h"
#include "application.h"

#include <iostream>

int main( int argc, char* argv[] )
{

    using namespace cogui;

    int bb = 0;

    cogui::application app(argc, argv,
                           arguments::on_arg("f") = [&bb](std::vector<std::string> params) {
                                    for(const auto& farg : params) {
                                        log_info() << "fs arg:" << farg;
                                    }
                                    log_info() << "arg f:" << params.size();
                                    bb++;
                           });

    log_info() << "bb called:" << bb;


    auto a = cogui::window(5, 5, 70, 15, L"Raise your \U0001F450",
                           window::on_resize = [](window* win, int w,int h){log_info() << "(lambda slot) new size:" << w << "x" << h;},
                           window::on_close  = [&](window* w){log_info() << "Closing this window"; app.exit(1);},
                           window::on_mouse_down = [](window* w, cogui::mouse::button b, int x, int y){log_info() << "Mouse (" << mouse::get().buttonName(b) << ") down:" << x << ", " << y; },
                           window::on_mouse_up = [](window* w, cogui::mouse::button b, int x, int y){log_info() << "Mouse (" << mouse::get().buttonName(b) << ") up:" << x << ", " << y; },
                           window::sysmenu = menu{
                               {L"&Select", action::selectable, action::on_trigger = [](action*){log_info() << "Clicked Select";}},
                               {L"No select", action::on_trigger = [](action*){log_info() << "Clicked No select";}}
                           }
    );

    auto& b = a.add_button(5,5, 10, 2, L"&Vertical layout",
                           button::on_click = [&a](button*){log_info() << "Thanks";
                                a.setLayout<cogui::layout::vertical>().expand(2);
                                a.redraw();
                           }
    );

    auto& c = a.add_button(35,5, 20, 2, L"&Horizontal layout",
                           button::on_click = [&a](button*){log_info() << "Thanks";
                                a.setLayout<cogui::layout::horizontal>().expand(1);
                                a.redraw();
                           }
    );
    auto& d = a.add_button(35,5, 5, 2, L"G&rid layout",
                           button::on_click = [&a](button*){log_info() << "Thanks";
                                a.setLayout<cogui::layout::grid>(2, 2);
                                a.redraw();
                           }
    );

    auto& e = a.add_button(35,5, 5, 2, L"B");
    auto& f = a.add_button(35,5, 5, 2, L"C");
    auto& g = a.add_button(35,5, 5, 2, L"D");
    auto& h = a.add_button(35,5, 5, 2, L"E");

    miso::connect(&a, a.sig_on_resize, [](window* win, int w, int h){log_info() << "(slot) new size:" << w << "x" << h;});
    miso::connect(&c, c.sig_on_click, [](button*){ log_info() << "You clicked me...:" ;});

    a.setLayout<cogui::layout::grid>(3, 3);

    app.run();

}
