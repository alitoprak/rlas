#pragma once

#include <raylib.h>
#include <angelscript.h>
#include <string>

namespace rlas
{

using app_log_level = TraceLogLevel;
struct app_params
{
    app_log_level log_level = LOG_NONE;
    int target_fps = 60;
};

struct window_params
{
    int width = 1280, height = 720;
    std::string title = "rlas game";
};

void register_api(asIScriptEngine* script_engine);

};