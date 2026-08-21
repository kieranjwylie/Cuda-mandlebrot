#include "complex.hpp"
#include "mandle.hpp"
#include <iostream>
#include <mpi.h>

void mandlebrot_calc(const Complex<double>& c, const int its, double& modz) {
    Complex<double> z(0.0, 0.0);
    for (int i = 1; i < its; i++) { 
        z = z*z + c;
        if (z.mod() > 2.0){
          modz = 0.0;
          return;
        }
    }
    modz = z.mod();
}

void complex_loop(Parallel_info comms, Vertex<double> vertices, const int its, std::vector<double> &modz, const std::vector<int> &vertices_per_thread, const std::vector<int> & start_points)
{
    int idx = comms.rank;
    int num_vertices = vertices_per_thread[idx];
    int start_point = start_points[idx];

    double local_modz = -1.0; // Initialize local_modz to -1.0 for each thread

    for (int i_vertex = 0; i_vertex < num_vertices; ++i_vertex) {
        Complex<double> c(vertices.x[vertices.xidx[i_vertex]], vertices.y[vertices.yidx[i_vertex]]);
        mandlebrot_calc(c, its, local_modz);

        modz[i_vertex] = local_modz;
    }

    return;
}

int mandle(Parallel_info comms, Vertex<double> vertices, const int its, std::vector<double> &global_modz, const std::vector<int> &vertices_per_thread, const std::vector<int> & start_points) 
{
    std::vector<double> modz;

    // Init modz locally
    modz.resize(vertices_per_thread[comms.rank]);
    for (int i = 0; i < vertices_per_thread[comms.rank]; i++) {
      modz[i] = 0.0;
    }

    double start = MPI_Wtime();
    // Execute
    complex_loop(comms, vertices, its, modz, vertices_per_thread, start_points);


    // MPI COMMS - Local arrays gathered into one global array
    int ierr = MPI_Gatherv(modz.data(), vertices_per_thread[comms.rank], MPI_DOUBLE, global_modz.data(), vertices_per_thread.data(), 
                           start_points.data(), MPI_DOUBLE, comms.boss_rank, MPI_COMM_WORLD);
    
    double end = MPI_Wtime();
    double elapsed_time = end - start;

    //if (comms.boss) {std::cout << "Elapsed time: " << elapsed_time << " ms" << std::endl;}
    if (comms.boss) {std::cout << elapsed_time << std::endl;}
    return 0;
}
