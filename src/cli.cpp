#include "cli.hpp"
#include <iostream>
#include <stdio.h>


int read_command_line(int argc, char *argv[], Command_Line & cl_options) 
{
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-b") {
            cl_options.blocks= atoi(argv[++i]);
        }
        else if (arg == "-t") {
            cl_options.threads= atoi(argv[++i]);
        }
        else if (arg == "-o") {
            cl_options.output_device_props = true;
        }
        else if (arg == "-i") {
            cl_options.config_file = argv[++i];
        }
        else if (arg == "--vertex_dist") {
            cl_options.output_vertex_dist = true;
        }

        else if (arg == "-h") {
            std::cout << "Usage: " << argv[0] << " [options]\n"
                      << "Options:\n"
                      << "  -b <value>    Set the number of blocks\n"
                      << "  -t <value>    Set the number of threads per block\n"
                      << "  -o            Output device properties\n"
                      << "  -i <value>    Set the configuration file\n"
                      << "  -h            Show this help message\n"
                      << "  --vertex_dist Output the vertex distribution per thread\n";

            return 1;
        }
        else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            return -1;
        }
    }
    return 0;
}
