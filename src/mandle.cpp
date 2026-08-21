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
        int vertex_idx = start_point + i_vertex;
        Complex<double> c(vertices.x[vertices.xidx[vertex_idx]], vertices.y[vertices.yidx[vertex_idx]]);
        mandlebrot_calc(c, its, local_modz);

        modz[vertex_idx] = local_modz;
    }

    return;
}

int mandle(Parallel_info comms, Vertex<double> vertices, const int its, std::vector<double> &modz, const std::vector<int> &vertices_per_thread, const std::vector<int> & start_points) 
{
    // Init modz
    modz.resize(vertices.nv);
    for (int i = 0; i < vertices.nv; i++) {
      modz[i] = 0.0;
    }

    // Execute
    complex_loop(comms, vertices, its, modz, vertices_per_thread, start_points);

    // Each rank (should) onyl edit its corresponding vertices. So all reduce
    MPI_Allreduce(MPI_IN_PLACE, modz.data(), modz.size(), MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    //std::cout << "Elapsed time: " << elapsed_time << " ms" << std::endl;

    return 0;
}
