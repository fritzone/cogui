#include "cogui.h"
#include "application.h"

#include <iostream>

void b_handler(cogui::button* b)
{
	b->set_title(L"Clicked");
}

void chk_click_handler(cogui::checkbox* cb)
{
	log_info() << "click handler:" << cb->is_checked() ;
	cb->set_title(cb->is_checked() ? L"C:Checked" : L"C:Unchecked");
}


int main( int argc, char* argv[] )
{

    using namespace cogui;

    int bb = 0;

    cogui::application app(argc, argv,
                            arguments::on_flag("f", "field selector", arguments::accepted_parameters{"a", "b"} ) = [&bb](std::vector<std::string> params)
                            {
                                    for(const auto& farg : params)
                                    {
                                        log_info() << "fs arg:" << farg;
                                    }
                                    log_info() << "arg f:" << params.size();
                                    bb++;
                            },
                            arguments::on_flag("s", "state selector") = [&bb](std::vector<std::string> params)
                            {
                                     for(const auto& farg : params)
                                     {
                                         log_info() << "s's arg:" << farg;
                                     }
                                     log_info() << "arg s:" << params.size();
                                     bb++;
                            }
    );

    log_info() << "bb called:" << bb;

	std::shared_ptr<button> b;

	auto a = cogui::window(5, 5, 70, 15, L"A not so special window",
                           window::on_resize = [](window*, int w, int h){log_info() << "(lambda slot) new size:" << w << "x" << h;},
                           window::on_close  = [&](window*){log_info() << "Closing this window"; app.exit(1);},
                           window::on_mouse_down = [](window* w, cogui::mouse::button b, int x, int y){log_info() << "Mouse (" << mouse::get().buttonName(b) << ") down:" << x << ", " << y; },
                           window::on_mouse_up = [](window* w, cogui::mouse::button b, int x, int y){log_info() << "Mouse (" << mouse::get().buttonName(b) << ") up:" << x << ", " << y; },
                           window::sysmenu = menu{
                               {L"&Select", action::checkable = true, action::on_trigger = [](action*){log_info() << "Clicked Select";}},
                               {L"No select", action::on_trigger = [](action*){log_info() << "Clicked No select";}}
                           },
                           window::mainmenu = menubar {

                                menu {
                                        L"&File",
                                        {
                                            {"&New",  action::on_trigger = [](action*){log_info() << "New Clicked";}},
                                            {L"&Open", action::on_trigger = [](action*){log_info() << "Open Clicked";}},
                                            {L"&Save", action::checkable = true, action::on_trigger = [](action*){log_info() << "Save Clicked";}},
                                            menu::separator_item,
                                            {L"&Exit", action::on_trigger = [&](action*){app.exit(1);}}
                                        }
                                },
                                menu {
                                        L"&Edit",
                                        {
											{L"&Copy", action::on_trigger = [&b](action*){log_info() << "New Clicked";
																						  b->set_title(L"Buu");}
											},
                                            {L"&Paste", action::on_trigger = [](action*){log_info() << "Open Clicked";}}
                                        }
                                },
                                menubar::align_right_after,
                                menu {
                                        L"&Help",
                                        {
                                            {L"&About",  action::on_trigger = [](action*){log_info() << "About Clicked";}},
                                        }
                                },
                                menu {
                                        L"&Purchase",
                                        {
                                            {L"&About", action::on_trigger = [](action*){log_info() << "About Clicked";}},
                                        }
                                }

                           },
                           window::on_keypress = [&](window* w, std::shared_ptr<cogui::key> k){
                                log_info() << "pressed a key:" << k->get_character();
                                w->set_title(k->get_character());
                           },
                           window::hotkeys = hotkey_associations {
                               on(Ctrl_b) = [&](window*){app.exit();}
                           },
                           window::scrollbars = scrollbar::horizontal
                           /*  */
    );

	b = a.add_button(5,5, 10, 2, L"&Vertical layout",
						   button::on_click = [&a](button*){log_info() << "Thanks";
								a.set_layout<cogui::layout::vertical>().expand(2);
                                a.redraw();
						   }
    );

	auto c = a.add_button(35,5, 20, 2, L"&Horizontal layout",
						   button::on_click = [&a](button* btn){ btn->set_title(L"Thanks");
								a.set_layout<cogui::layout::horizontal>().expand(1);
						   }
	);
	auto d = a.add_button(35,5, 5, 2, L"G&rid layout",
						   button::on_click = [&a](button*){log_info() << "Thanks";
								a.set_layout<cogui::layout::grid>(4, 4);
						   }
	);
	auto f = a.add_button(35,5, 5, 2, L"C", button::on_click = b_handler);

    auto e = a.add_checkbox(35,5, 5, 2, L"Check me!", checkbox::checked = false,
							 checkbox::on_state_change = [&f](checkbox*, bool checked) {
								log_info() << "check state change lambda:" << checked;
								f->set_title(checked ? L"Checked" : L"Unchecked");
							 },
                             checkbox::on_click = chk_click_handler
	);
	auto g = a.add_radiobutton(55,5, 5, 2, "Some radion",
						   radiobutton::on_state_change = [&e](radiobutton*, bool cs){
								log_info() << "Thanks";
								e->set_checked( cs );
	});


	auto rbg = a.add_radiobutton_group(10, 10, L"Stuff",
									   {
										   {L"The first stuff", radiobutton::on_state_change = [](radiobutton*,bool){log_info() << "First stuff click";} },
										   {L"The second stuff"},
										   {L"The third stuff"}
                                       },
                                       radiobutton_group::on_state_change = [](radiobutton_group* rbg, int seli) {
                                            log_info() << "RBG item:" << seli;
                                       }
	);


	miso::connect(&a, a.sig_on_resize, [](window* win, int w, int h){log_info() << "(slot) new size:" << w << "x" << h;});
	miso::connect(&c, c->sig_on_click, [](button*){ log_info() << "You clicked me...:" ;});

//    auto w2 = cogui::window(5, 28, 70, 10, L"Another window");

//	auto h = a.add_button(35,5, 5, 2, L"E", button::on_click = [&](button*) {w2.close();});

	//a.setLayout<cogui::layout::grid>(3, 3);

    app.run();

}

