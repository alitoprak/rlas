#include <angelscript.h>
#include <scriptstdstring.h>
#include <scriptbuilder.h>
#include <raylib.h>

namespace rlas
{
    static void clear_background(uint8_t r, uint8_t g, uint8_t b)
    {
        ClearBackground({ r, g, b, 255 });
    }
};

static int include_callback(const char* include, const char* from, CScriptBuilder* builder, void* user_param)
{
    builder->AddSectionFromFile(include);
    return 0;
}

int main(int arg_count, char* args[])
{
    asIScriptEngine* engine = asCreateScriptEngine();

    RegisterStdString(engine);

    engine->RegisterGlobalFunction("void clear_background(uint8, uint8, uint8)", asFUNCTION(rlas::clear_background), asCALL_CDECL);

    CScriptBuilder builder;
    builder.SetIncludeCallback(include_callback, nullptr);
    builder.StartNewModule(engine, "rlas_module");
    builder.AddSectionFromFile("main.as");
    builder.BuildModule();

    asIScriptModule* mod = engine->GetModule("rlas_module");
    asIScriptFunction* setup_func = mod->GetFunctionByDecl("void setup(int &out, int &out, string &out, int &out)");
    asIScriptFunction* frame_func = mod->GetFunctionByDecl("void frame()");
    asIScriptFunction* cleanup_func = mod->GetFunctionByDecl("void cleanup()");

    if (setup_func && frame_func && cleanup_func)
    {
        asIScriptContext* ctx = engine->CreateContext();
        
        int window_width = 1280;
        int window_height = 720;
        std::string window_title = "rlas game";
        int target_fps = 60;
        
        ctx->Prepare(setup_func);
        ctx->SetArgAddress(0, &window_width);
        ctx->SetArgAddress(1, &window_height);
        ctx->SetArgAddress(2, &window_title);
        ctx->SetArgAddress(3, &target_fps);
        ctx->Execute();

        InitWindow(window_width, window_height, window_title.c_str());
        SetTargetFPS(target_fps);

        while (!WindowShouldClose())
        {
            BeginDrawing();

            ctx->Prepare(frame_func);
            ctx->Execute();

            EndDrawing();
        }

        ctx->Prepare(cleanup_func);
        ctx->Execute();

        CloseWindow();

        ctx->Release();
    }

    engine->ShutDownAndRelease();

    return 0;
}