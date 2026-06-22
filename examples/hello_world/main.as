void setup(app_params &out app, window_params &out window)
{
    app.log_level = app_log_level::none;
    app.target_fps = 60;

    window.width = 512;
    window.height = 512;
    window.title = "hello world";
}

float timer = 0;
color black_color(0, 0, 0, 255);
color white_color(255, 255, 255, 255);

void frame(float delta_time)
{
    timer += delta_time;

    if (timer <= 1)
    {
        clear_background(black_color);
        draw_text("hello world", 4, 4, 24, white_color);
    }
    else if (timer <= 2)
    {
        clear_background(white_color);
        draw_text("hello world", 4, 4, 24, black_color);
    }
    else
    {
        timer = 0;
    }
}

void cleanup()
{

}
