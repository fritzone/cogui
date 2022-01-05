#include <input_provider.h>

#include <events.h>

struct Gpm_Event;

namespace cogui {

namespace input_providers {

class gpm_input : public input_provider
{
public:
    gpm_input() = default;
    ~gpm_input();
    bool init() override;
    bool shutdown() override;
    std::vector<std::shared_ptr<cogui::events::event>> get_next_event() override;
    std::string name() const override;
    static int my_handler(Gpm_Event *event, void *);

private:
    std::vector<std::shared_ptr<cogui::events::event>> m_events;
    int gpmFd;
    int prev_curs = 1;

};
}
}
