#include "rlas_api.h"

#include <scriptstdstring.h>
#include <scriptbuilder.h>

namespace rlas
{

void window_params_construct(window_params* self)
{
    new(self) window_params();
}

void window_params_destruct(window_params* self)
{
    self->~window_params();
}

static void color_construct(uint8_t r, uint8_t g, uint8_t b, uint8_t a, color* self)
{
    self->r = r;
    self->g = g;
    self->b = b;
    self->a = a;
}

void rl_clear_background(const color& color)
{
    ClearBackground(color);
}

void rl_draw_text(const std::string& text, int pos_x, int pos_y, int font_size, const color& color)
{
    DrawText(text.c_str(), pos_x, pos_y, font_size, color);
}

void register_api(asIScriptEngine* script_engine)
{
    RegisterStdString(script_engine);

    script_engine->RegisterEnum("app_log_level");
    script_engine->RegisterEnumValue("app_log_level", "all", static_cast<int>(app_log_level::all));
    script_engine->RegisterEnumValue("app_log_level", "trace", static_cast<int>(app_log_level::trace));
    script_engine->RegisterEnumValue("app_log_level", "debug", static_cast<int>(app_log_level::debug));
    script_engine->RegisterEnumValue("app_log_level", "info", static_cast<int>(app_log_level::info));
    script_engine->RegisterEnumValue("app_log_level", "warning", static_cast<int>(app_log_level::warning));
    script_engine->RegisterEnumValue("app_log_level", "error", static_cast<int>(app_log_level::error));
    script_engine->RegisterEnumValue("app_log_level", "fatal", static_cast<int>(app_log_level::fatal));
    script_engine->RegisterEnumValue("app_log_level", "none", static_cast<int>(app_log_level::none));

    script_engine->RegisterObjectType("app_params", sizeof(app_params), asOBJ_VALUE | asOBJ_POD);
    script_engine->RegisterObjectProperty("app_params", "app_log_level log_level", asOFFSET(app_params, log_level));
    script_engine->RegisterObjectProperty("app_params", "int target_fps", asOFFSET(app_params, target_fps));

    script_engine->RegisterObjectType("window_params", sizeof(window_params), asOBJ_VALUE | asOBJ_APP_CLASS_CD);
    script_engine->RegisterObjectBehaviour("window_params", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(window_params_construct), asCALL_CDECL_OBJLAST);
    script_engine->RegisterObjectBehaviour("window_params", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(window_params_destruct), asCALL_CDECL_OBJLAST);
    script_engine->RegisterObjectProperty("window_params", "int width", asOFFSET(window_params, width));
    script_engine->RegisterObjectProperty("window_params", "int height", asOFFSET(window_params, height));
    script_engine->RegisterObjectProperty("window_params", "string title", asOFFSET(window_params, title));

    script_engine->RegisterObjectType("color", sizeof(color), asOBJ_VALUE | asOBJ_POD);
    script_engine->RegisterObjectBehaviour("color", asBEHAVE_CONSTRUCT, "void f(uint8, uint8, uint8, uint8)", asFUNCTION(color_construct), asCALL_CDECL_OBJLAST);

    script_engine->RegisterGlobalFunction("void clear_background(const color &in)", asFUNCTION(rl_clear_background), asCALL_CDECL);
    script_engine->RegisterGlobalFunction("void draw_text(const string &in, int, int, int, const color &in)", asFUNCTION(rl_draw_text), asCALL_CDECL);
}

};