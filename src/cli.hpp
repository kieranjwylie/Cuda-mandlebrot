#include <cstdint>

struct Command_Line
{
    char * config_file = nullptr; // Path to the configuration file
    int64_t blocks  = 256;  // Number of blocks
    int64_t threads = 256;  // Number of threads per block
    bool output_device_props = false; 
    bool output_vertex_dist = false;
};

int read_command_line(int argc, char *argv[], Command_Line & cl_options);
