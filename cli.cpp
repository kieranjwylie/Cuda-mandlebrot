#include "cli.hpp"
#include <iostream>
#include <stdio.h>


int read_command_line(int argc, char *argv[], Command_Line & cl_options) 
{
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-xl") {
            cl_options.xl= atof(argv[++i]);
        }
        else if (arg == "-xh") {
            cl_options.xh= atof(argv[++i]);
        }
        else if (arg == "-yl") {
            cl_options.yl= atof(argv[++i]);
        }
        else if (arg == "-yh") {
            cl_options.yh= atof(argv[++i]);
        }
        else if (arg == "-b") {
            cl_options.blocks= atoi(argv[++i]);
        }
        else if (arg == "-t") {
            cl_options.threads= atoi(argv[++i]);
        }
        else if (arg == "-o") {
            cl_options.output_device_props = true;
        }
        else if (arg == "-i") {
            cl_options.its = atoi(argv[++i]);
        }
        else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            return -1;
        }
    }
    return 0;
}
