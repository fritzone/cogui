#ifndef EXTENSION_H
#define EXTENSION_H


extern std::string g_s_theme_name;
extern std::string g_s_input_provider_name;
extern std::string g_s_rendering_engine_name;

extern std::vector<std::string> g_s_all_themes;
extern std::vector<std::string> g_s_all_rendering_engines;
extern std::vector<std::string> g_s_all_input_providers;


namespace cogui
{

struct extension
{
    virtual ~extension() = default;
    /**
     * @brief init will initialize the extension manager, ie. identify the libraries
     * @param argc
     * @param argv
     */
    static void init(int argc, char* argv []);
};

}

#endif // EXTENSION_H
