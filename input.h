#ifndef INPUT_H
#define INPUT_H

#include "events.h"

#include <vector>

namespace cogui {

/**
 * @brief The input class is a basic class that will deal with the user input (keyboard/mouse)
 */
class input
{
public:
    virtual bool init() = 0;
    virtual bool shutdown() = 0;
    virtual std::vector<cogui::event> get_next_event() = 0;

};

class xterm_input : public input
{
public:
    bool init() override;
    bool shutdown() override;
    std::vector<cogui::event> get_next_event() override;
};

class gpm_input : public input
{
public:
    gpm_input();
    ~gpm_input();
    bool init() override;
    bool shutdown() override;
    std::vector<cogui::event> get_next_event() override;
};



}
#endif // INPUT_H
