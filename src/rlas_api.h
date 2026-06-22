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
void window_params_construct(window_params* mem);
void window_params_destruct(window_params* mem);

using color = Color;

void rl_clear_background(const color& color);
void rl_draw_text(const std::string& text, int pos_x, int pos_y, int font_size, const color& color);

void register_api(asIScriptEngine* script_engine);

};