#include "desktop.h"
#include "window.h"
#include "application.h"

#include "loguru.h"

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

void do_resize(int dummy)
{
     exit(66);
}

int main( int argc, char* argv[] )
{
    // Optional, but useful to time-stamp the start of the log.
    // Will also detect verbosity level on command line as -v.
    loguru::init(argc, argv);

    // Put every log message in "everything.log":
    loguru::add_file("everything.log", loguru::Append, loguru::Verbosity_MAX);

    loguru::g_stderr_verbosity = loguru::Verbosity_OFF;

    signal(SIGWINCH, do_resize);

    cogui::desktop::get();


    cogui::window a(5,5,70,15);
    a.draw();

    cogui::application app;
    app.run();

}
