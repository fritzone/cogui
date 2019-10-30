#ifndef APPLICATION_H
#define APPLICATION_H

#include "events.h"

namespace cogui
{

class application
{
public:
    application();

    application(const application&) = delete;
    application(application&&) = delete;

    application& operator = (const application&) = delete;
    application& operator = (application&&) = delete;

    int run();

    bool running() const;

    void stop();

private:
    void handle_event(cogui::event c);

    bool m_running = false;
};

}

#endif // APPLICATION_H
