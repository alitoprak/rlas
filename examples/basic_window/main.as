void setup(app_params &out app, window_params &out window)
{
    app.log_level = app_log_level::all;
    app.target_fps = 60;

    window.width = 800;
    window.height = 450;
    window.title = "raylib [core] example - basic window";
}

void frame(float delta_time)
{
    clear_background(color(255, 255, 255, 255));
    draw_text("Congrats! You created your first window!", 190, 200, 20, color(127, 127, 127, 255));
}

void cleanup()
{

}
