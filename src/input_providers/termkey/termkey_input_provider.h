#include <input_provider.h>

#include <events.h>

namespace cogui {

namespace input_providers {


class termkey_input : public cogui::input_provider
{
public:
    termkey_input() = default;
    ~termkey_input() = default;
    bool init() override;
    bool shutdown() override;
	std::string name() const override;

	std::vector<std::shared_ptr<events::event>> get_next_event() override;
    TermKey *tk;
    int prev_curs = 1;
	static std::map<TermKeySym, events::key_class> m_keymap;

};

}

}
