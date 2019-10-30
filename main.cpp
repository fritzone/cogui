#include "cogui.h"
#include "loguru.h"

int main( int argc, char* argv[] )
{
    cogui::init(argc, argv);

    using namespace cogui;

    auto a = cogui::window(/*control::x = */5,
                           /*control::y = */5,
                           /*control::width = */70,
                           /*control:: height = */15,
                           /*control::title = */L"A window with title",
                           window::on_resize = [](window* win, int w,int h){info() << "(lambda slot) new size:" << w << "x" << h;},
                           window::on_close  = [](window* w){info() << "Closing this window"; },
                           window::on_mouse_down = [](window* w, cogui::mouse::button b, int x, int y){info() << "Mouse (" << mouse::get().buttonName(b) << ") down:" << x << ", " << y; },
                           window::on_mouse_up = [](window* w, cogui::mouse::button b, int x, int y){info() << "Mouse (" << mouse::get().buttonName(b) << ") up:" << x << ", " << y; }
    );

    auto& b = a.add_button(5,5, 10, 2, L"Click Me",
                           button::on_click = [](button*){info() << "Thanks";}
    );

    auto& c = a.add_button(35,5, 20, 2, L"Don't Click Me",
                           button::on_click = [](button*){ info() << "You clicked me...:" ;}
    );

    miso::connect(&a, a.sig_on_resize, [](window* win, int w, int h){info() << "(slot) new size:" << w << "x" << h;});

    cogui::application app;
    app.run();

}
