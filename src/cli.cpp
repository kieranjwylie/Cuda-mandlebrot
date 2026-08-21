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
        else if (arg == "-nx") {
            cl_options.nx = atoi(argv[++i]);
        }
        else if (arg == "-ny") {
            cl_options.ny = atoi(argv[++i]);
        }
        else if (arg == "-h") {
            std::cout << "Usage: " << argv[0] << " [options]\n"
                      << "Options:\n"
                      << "  -xl <value>   Set the lower x bound\n"
                      << "  -xh <value>   Set the upper x bound\n"
                      << "  -yl <value>   Set the lower y bound\n"
                      << "  -yh <value>   Set the upper y bound\n"
                      << "  -b <value>    Set the number of blocks\n"
                      << "  -t <value>    Set the number of threads per block\n"
                      << "  -o            Output device properties\n"
                      << "  -i <value>    Set the number of iterations\n"
                      << "  -nx <value>   Set the number of x nodes\n"
                      << "  -ny <value>   Set the number of y nodes\n"
                      << "  -h            Show this help message\n";
            return 1;
        }
        else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            return -1;
        }
    }
    return 0;
}
