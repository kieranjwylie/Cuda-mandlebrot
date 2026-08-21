#include "parallel.hpp"
#include <iostream>


// Distribute the nodes evenly per thread, do no worry about the blocks
void distribute_nodes(Vertex<double> vertices, std::vector<int> & vertices_per_thread, std::vector<int> & start_points, int threads) {
    int n_nodes = vertices.nv; // Total number of nodes

    int n_vertices_per_thread = n_nodes / threads;
    int remainder = n_nodes % threads;

    // Set an array for each thread to know how many vertices it is responsible for
    vertices_per_thread.resize(threads);
    start_points.resize(threads);
    int vertex_sum = 0;
    for (int i = 0; i < threads; i++) {
        vertices_per_thread[i] = n_vertices_per_thread;
        if (i < remainder) {
            vertices_per_thread[i]++;
        }
        start_points[i] = vertex_sum;
        vertex_sum += vertices_per_thread[i];
    }

    // Work out the start point for each thread
}

void output_vertex_dist(Vertex<double> vertices, std::vector<int> vertices_per_thread, std::vector<int> & start_points, int threads) {
    std::cout << "Total number of vertices: " << vertices.nv << std::endl;
    std::cout << "Number of threads: " << threads << std::endl;
    for (int i = 0; i < threads; i++) {
        std::cout << "Thread " << i << ": " << vertices_per_thread[i] << " vertices, starts at  " << start_points[i] << std::endl;
    }
}