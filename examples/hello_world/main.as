void setup(app_params &out app, window_params &out window)
{
    app.log_level = app_log_level::none;
    app.target_fps = 60;

    window.width = 512;
    window.height = 512;
    window.title = "hello world";
}

void frame()
{
    clear_background(255, 255, 255);
}

void cleanup()
{

}
