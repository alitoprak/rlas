#pragma once

#include <raylib.h>
#include <angelscript.h>
#include <string>

namespace rlas
{

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

inline TraceLogLevel app_log_level_to_real(app_log_level log_level)
{
    TraceLogLevel real_log_level;
    switch (log_level)
    {
    case app_log_level::all:
        real_log_level = LOG_ALL;
        break;
    case app_log_level::trace:
        real_log_level = LOG_TRACE;
        break;
    case app_log_level::debug:
        real_log_level = LOG_DEBUG;
        break;
    case app_log_level::info:
        real_log_level = LOG_INFO;
        break;
    case app_log_level::warning:
        real_log_level = LOG_WARNING;
        break;
    case app_log_level::error:
        real_log_level = LOG_ERROR;
        break;
    case app_log_level::fatal:
        real_log_level = LOG_FATAL;
        break;
    case app_log_level::none:
    default:
        real_log_level = LOG_NONE;
        break;
    }
    return real_log_level;
}

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

using color = Color;

void rl_clear_background(const color& color);
void rl_draw_text(const std::string& text, int pos_x, int pos_y, int font_size, const color& color);

void register_api(asIScriptEngine* script_engine);

};