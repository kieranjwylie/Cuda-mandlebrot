
#include <iostream>
#include <stdio.h>

#include "cli.hpp"
#include "grid.hpp"
#include "data.hpp"
#include "mandle.cuh"
#include "output.hpp"


int main(int argc, char *argv[]){

    double xl, xh, yl, yh;
    int ierr, nx, ny;

    Command_Line command_line_args;
    Vertex<double> vertices;
    std::vector<double> modz;


    ierr = read_command_line(argc, argv, command_line_args);

    if (command_line_args.output_device_props) {
        output_device_props();
    }

    xl = command_line_args.xl;
    xh = command_line_args.xh;
    yl = command_line_args.yl;
    yh = command_line_args.yh;

    int n_tot = command_line_args.blocks*command_line_args.threads;

    nx = command_line_args.threads;
    ny = command_line_args.blocks;

    setup_grid(xl, xh, yl, yh, nx, ny, vertices);

    mandle(vertices, command_line_args.blocks, command_line_args.threads, command_line_args.its, modz);

    write_mandle(vertices, modz);
    write_mandle_bin(vertices, modz);
}
