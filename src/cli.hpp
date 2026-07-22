
struct Command_Line
{
    // Solution bounds
    double xl = -2.0; 
    double xh = 1.0;
    double yl = -1.0;
    double yh = 1.0;
    int blocks  = 256;
    int threads = 256;
    int its     = 100;
    bool output_device_props = false; 
};

int read_command_line(int argc, char *argv[], Command_Line & cl_options);
