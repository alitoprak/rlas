#pragma once

#include <angelscript.h>

namespace rlas
{

constexpr char k_module_name[] = "rlas";

void build_module(asIScriptEngine* script_engine, const char* main_file_path);

inline asIScriptModule* get_module(asIScriptEngine* script_engine)
{
    return script_engine->GetModule(k_module_name);
}

};