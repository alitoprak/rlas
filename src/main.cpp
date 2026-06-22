#include "rlas_api.h"

int main(int arg_count, char* args[])
{
    asIScriptEngine* script_engine = asCreateScriptEngine();

    rlas::register_api(script_engine);

    rlas::build_module(script_engine, "main.as");

    asIScriptModule* rlas_module = rlas::get_module(script_engine);
    asIScriptFunction* setup_function = rlas_module->GetFunctionByDecl("void setup(app_params &out, window_params &out)");
    asIScriptFunction* frame_function = rlas_module->GetFunctionByDecl("void frame()");
    asIScriptFunction* cleanup_function = rlas_module->GetFunctionByDecl("void cleanup()");

    if (setup_function && frame_function && cleanup_function)
    {
        asIScriptContext* script_context = script_engine->CreateContext();
        
        rlas::app_params app_params {};
        rlas::window_params window_params {};
        
        script_context->Prepare(setup_function);
        script_context->SetArgAddress(0, &app_params);
        script_context->SetArgAddress(1, &window_params);
        script_context->Execute();

        
        SetTraceLogLevel(rlas::app_log_level_to_real(app_params.log_level));
        SetTargetFPS(app_params.target_fps);
        InitWindow(window_params.width, window_params.height, window_params.title.c_str());

        while (!WindowShouldClose())
        {
            BeginDrawing();

            script_context->Prepare(frame_function);
            script_context->Execute();

            EndDrawing();
        }

        script_context->Prepare(cleanup_function);
        script_context->Execute();

        CloseWindow();

        script_context->Release();
    }

    script_engine->ShutDownAndRelease();

    return 0;
}