#ifndef INPUT_H
#define INPUT_H

#include "events.h"
#include <termkey.h>

#include <vector>
#include <string>
#include <map>

namespace cogui {



/**
 * @brief The input class is a basic class that will deal with the user input (keyboard/mouse)
 */
class input
{
public:
    virtual ~input() = default;
    virtual bool init() = 0;
    virtual bool shutdown() = 0;
    virtual std::vector<std::shared_ptr<cogui::events::event>> get_next_event() = 0;

};

class xterm_input : public input
{
public:
    bool init() override;
    bool shutdown() override;
    std::vector<std::shared_ptr<cogui::events::event>> get_next_event() override;
};

class gpm_input : public input
{
public:
    gpm_input() = default;
    ~gpm_input();
    bool init() override;
    bool shutdown() override;
    std::vector<std::shared_ptr<cogui::events::event>> get_next_event() override;
};

class termkey_input : public input
{
public:
    termkey_input() = default;
    ~termkey_input() = default;
    bool init() override;
    bool shutdown() override;
    std::vector<std::shared_ptr<cogui::events::event>> get_next_event() override;
    TermKey *tk;
    int prev_curs = 1;
    static std::map<TermKeySym, cogui::events::key_class> m_keymap;

};

}
#endif // INPUT_H
