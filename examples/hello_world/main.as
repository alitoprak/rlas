void setup(app_params &out app, window_params &out window)
{
    app.log_level = app_log_level::none;
    app.target_fps = 60;

    window.width = 512;
    window.height = 512;
    window.title = "hello world";
}

float timer = 0;

void frame(float delta_time)
{
    timer += delta_time;

    if (timer <= 1)
    {
        clear_background(0, 0, 0);
    }
    else if (timer <= 2)
    {
        clear_background(255, 255, 255);
    }
    else
    {
        timer = 0;
    }
}

void cleanup()
{

}
