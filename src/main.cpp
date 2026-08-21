
#include <iostream>
#include <stdio.h>

#include "cli.hpp"
#include "grid.hpp"
#include "data.hpp"
#include "mandle.hpp"
#include "output.hpp"
#include "parallel.hpp"
#include "json_parser/parse_json.hpp"
#include "json_parser/settings.hpp"

#include "mpi_utils.hpp"
#include <mpi.h>
int main(int argc, char *argv[]){

    int ierr = MPI_Init(&argc, &argv);
    
    Parallel_info comms;
    ierr =  init_comms(comms);

    double xl, xh, yl, yh;
    int nx, ny;

    Command_Line command_line_args;
    Vertex<double> vertices;
    std::vector<double> modz;
    std::vector<int> vertices_per_thread;

    ierr = read_command_line(argc, argv, command_line_args);

    if (ierr != 0) {
        return ierr;
    }

    Problem_Settings settings;
    ierr = parse_json(command_line_args.config_file, settings);


    xl = settings.x_min;
    xh = settings.x_max;
    yl = settings.y_min;
    yh = settings.y_max;

    nx = settings.nx;
    ny = settings.ny;

    setup_grid(xl, xh, yl, yh, nx, ny, vertices);

    //distribute_nodes(vertices, vertices_per_thread, total_threads);
    distribute_nodes(vertices, vertices_per_thread, comms.size);
    
    if (command_line_args.output_vertex_dist && comms.boss) {
        output_vertex_dist(vertices, vertices_per_thread, comms.size);
    }

    mandle(comms, vertices, settings.its, modz, vertices_per_thread);

    if (comms.boss) {write_mandle(vertices, modz);}

    ierr = finalise_comms();
    //write_mandle_bin(vertices, modz);
}
