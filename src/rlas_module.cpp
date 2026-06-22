#include "rlas_module.h"

#include <scriptbuilder.h>

namespace rlas
{

static int script_include_callback(const char* include, const char* from, CScriptBuilder* script_builder, void* user_param)
{
    script_builder->AddSectionFromFile(include);
    return 0;
}

void build_module(asIScriptEngine* script_engine, const char* main_file_path)
{
    CScriptBuilder script_builder;
    script_builder.SetIncludeCallback(script_include_callback, nullptr);
    script_builder.StartNewModule(script_engine, k_module_name);
    script_builder.AddSectionFromFile(main_file_path);
    script_builder.BuildModule();
}

};