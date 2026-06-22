void setup(int &out window_width, int &out window_height, string &out window_title, int &out target_fps)
{
    window_width = 512;
    window_height = 512;
    window_title = "hello world";
    target_fps = 60;
}

void frame()
{
    clear_background(255, 255, 255);
}

void cleanup()
{

}
