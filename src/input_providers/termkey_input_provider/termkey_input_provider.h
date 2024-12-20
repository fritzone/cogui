#ifndef _TERMKEY_INPUT_PROVIDER_H_
#define _TERMKEY_INPUT_PROVIDER_H_
#include <input_provider.h>

#include <events.h>

namespace cogui {

namespace input_providers {


class termkey_input_provider : public cogui::input_provider
{
public:
    termkey_input_provider() = default;
    virtual ~termkey_input_provider();

    bool init() override;
    bool shutdown() override;
	std::string name() const override;

	std::vector<std::shared_ptr<events::event>> get_next_event() override;
    TermKey *tk = nullptr;
    int prev_curs = 1;
	static std::map<TermKeySym, events::key_class> m_keymap;

};

}

}

#endif
