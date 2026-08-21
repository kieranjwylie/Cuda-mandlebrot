
struct Command_Line
{
    // Solution bounds
    double xl = -2.0;   // Low x boud
    double xh = 1.0;    // High x bound
    double yl = -1.0;   // Low y bound
    double yh = 1.0;    // High y bound
    int nx      = 0;    // Number of x nodes
    int ny      = 0;    // Number of y nodes
    int blocks  = 256;  // Number of blocks
    int threads = 256;  // Number of threads per block
    int its     = 100;  // Number of mandebrot iterations
    bool output_device_props = false; 
};

int read_command_line(int argc, char *argv[], Command_Line & cl_options);
