
#include <iostream>
#include <stdio.h>

#include "cli.hpp"
#include "grid.hpp"
#include "data.hpp"
#include "mandle.cuh"
#include "output.hpp"
#include "parallel.hpp"
#include "json_parser/parse_json.hpp"
#include "json_parser/settings.hpp"

int main(int argc, char *argv[]){

    double xl, xh, yl, yh;
    int ierr, nx, ny;

    Command_Line command_line_args;
    Vertex<double> vertices;
    std::vector<double> modz;
    std::vector<int> vertices_per_thread, start_points;


    ierr = read_command_line(argc, argv, command_line_args);

    if (ierr != 0) {
        return ierr;
    }

    Problem_Settings settings;
    ierr = parse_json(command_line_args.config_file, settings);

    if (command_line_args.output_device_props) {
        output_device_props();
    }

    xl = settings.x_min;
    xh = settings.x_max;
    yl = settings.y_min;
    yh = settings.y_max;

    nx = settings.nx;
    ny = settings.ny;

    int total_threads = command_line_args.blocks * command_line_args.threads;

    setup_grid(xl, xh, yl, yh, nx, ny, vertices);

    distribute_nodes(vertices, vertices_per_thread, start_points, total_threads);
    if (command_line_args.output_vertex_dist) {
        output_vertex_dist(vertices, vertices_per_thread, start_points, total_threads);
    }

    mandle(vertices, command_line_args.blocks, command_line_args.threads, settings.its, modz, vertices_per_thread, start_points);

    write_mandle(vertices, modz);
    //write_mandle_bin(vertices, modz);
}
