#ifndef INPUT_PROVIDER_H
#define INPUT_PROVIDER_H

#include "events.h"
#include <termkey.h>

#include <vector>
#include <string>
#include <map>

namespace cogui {



/**
 * @brief The input class is a basic class that will deal with the user input (keyboard/mouse)
 */
class input_provider
{
public:

    static const char* type;
    static const char* path;


	virtual ~input_provider() = default;
    virtual bool init() = 0;
    virtual bool shutdown() = 0;
    virtual std::vector<std::shared_ptr<events::event>> get_next_event() = 0;

        virtual std::string name() const = 0;

};

}

#endif // INPUT_PROVIDER_H
