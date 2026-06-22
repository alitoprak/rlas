#pragma once

#include <string>
#include <stdint.h>
#include <raylib.h>
#include <angelscript.h>

namespace rlas
{
    constexpr char k_module_name[] = "asd";

    enum class app_log_level
    {
        all,
        trace,
        debug,
        info,
        warning,
        error,
        fatal,
        none
    };

    struct app_params
    {
        app_log_level log_level = app_log_level::none;
        int target_fps = 60;
    };
    
    struct window_params
    {
        int width = 1280, height = 720;
        std::string title = "rlas game";
    };
    void window_params_construct(window_params* mem);
    void window_params_destruct(window_params* mem);

    void rl_clear_background(uint8_t r, uint8_t g, uint8_t b);

    void register_api(asIScriptEngine* script_engine);
    void build_module(asIScriptEngine* script_engine, const char* main_file_path);

    inline asIScriptModule* get_module(asIScriptEngine* script_engine)
    {
        return script_engine->GetModule(k_module_name);
    }
};