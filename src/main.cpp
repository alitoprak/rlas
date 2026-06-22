#include <angelscript.h>
#include <scriptstdstring.h>
#include <scriptbuilder.h>
#include <raylib.h>

int g_window_width = 1280;
int g_window_height = 720;
std::string g_window_title = "rlas game";

void clear_background(uint8_t r, uint8_t g, uint8_t b)
{
    ClearBackground({ r, g, b, 255 });
}

int main(int arg_count, char* args[])
{
    asIScriptEngine* engine = asCreateScriptEngine();

    RegisterStdString(engine);

    engine->RegisterGlobalProperty("int g_window_width", &g_window_width);
    engine->RegisterGlobalProperty("int g_window_height", &g_window_height);
    engine->RegisterGlobalProperty("string g_window_title", &g_window_title);

    engine->RegisterGlobalFunction("void clear_background(uint8, uint8, uint8)", asFUNCTION(clear_background), asCALL_CDECL);

    CScriptBuilder builder;
    builder.StartNewModule(engine, "rlas_module");
    builder.AddSectionFromFile("main.as");
    builder.BuildModule();

    asIScriptModule* mod = engine->GetModule("rlas_module");
    asIScriptFunction* setup_func = mod->GetFunctionByDecl("void setup()");
    asIScriptFunction* frame_func = mod->GetFunctionByDecl("void frame()");
    asIScriptFunction* cleanup_func = mod->GetFunctionByDecl("void cleanup()");

    if (setup_func && frame_func && cleanup_func)
    {
        asIScriptContext* ctx = engine->CreateContext();

        ctx->Prepare(setup_func);
        ctx->Execute();

        InitWindow(g_window_width, g_window_height, g_window_title.c_str());


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