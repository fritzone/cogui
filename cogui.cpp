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
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "loguru.h"

void do_resize(int dummy)
{
     exit(66);
}



void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  LOG_S(INFO) << "Error: signal %d:\n" << sig;
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main( int argc, char* argv[] )
{
    // Optional, but useful to time-stamp the start of the log.
    // Will also detect verbosity level on command line as -v.
    loguru::init(argc, argv);

    LOG_SCOPE_FUNCTION(INFO);

    // Put every log message in "everything.log":
    loguru::add_file("everything.log", loguru::Append, loguru::Verbosity_MAX);

    loguru::g_stderr_verbosity = loguru::Verbosity_OFF;

    signal(SIGWINCH, do_resize);
    signal(SIGSEGV, handler);   // install our handler

    setenv("TERM", "linux", 1);
    cogui::desktop::get();


    cogui::window a(5,5,70,15);
    a.draw();

    cogui::application app;
    app.run();

}
