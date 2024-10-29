#include "desktop.h"
#include "window.h"
#include "application.h"
#include "rendering_engine.h"

#include "log.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <sstream>
#include <csignal>


#include <sys/ioctl.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "cogui.h"

#include "ncurses.h"

using namespace cogui;

void do_resize(int)
{
     log_info() << "Resize window";

     desktop::get().resize();
}

void handler(int sig)
{
    desktop::get().shutdown();

  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  log_critical() << "Error: signal: " << strsignal(sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

extern std::string g_s_theme_name;
extern std::string g_s_input_provider_name;
extern std::string g_s_rendering_engine_name;

extern std::vector<std::string> g_s_all_themes;
extern std::vector<std::string> g_s_all_rendering_engines;
extern std::vector<std::string> g_s_all_input_providers;

void cogui::init(int argc, char* argv [])
{
    cogui::extension_manager::init(argc, argv);

    signal(SIGWINCH, do_resize);
    signal(SIGSEGV, handler);
    signal(SIGINT, handler);

    cogui::desktop::init(g_);
    cogui::desktop::get();


}

cogui::textflags::operator int() const
{
    switch(m_value)
    {
    case v_normal: return A_NORMAL;
    case v_underline: return A_UNDERLINE;
    case v_bold: return A_BOLD;
    case v_title: return static_cast<int>(v_title);
    default: if(m_value) return static_cast<int>(m_value);
    }
    return A_NORMAL;
}

int textflags::operator &(const textflags &o) const
{
    int a = this->operator int();
    int b = static_cast<int>(o);

    return (a | b);
}

std::shared_ptr<cogui::rendering_engine> cogui::graphics()
{
	return desktop::get().get_graphics();
}

