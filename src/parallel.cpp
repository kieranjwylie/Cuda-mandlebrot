#include "parallel.hpp"
#include <iostream>
// // This is not strictly necessary for the mandlebrot code, but the following will domain decompose the problem per block
// void domain_decompose(Vertex<double> & vertices, block_data & blocks, int nblocks, int nthreads) {
//     int n_nodes = vertices.nv; // Total number of nodes

//     // Calculate the number of nodes per block
//     int nodes_per_block = (n_nodes + nblocks - 1) / nblocks;

//     // Distribute the nodes to each thread
//     for (int block = 0; block < blocks; ++block) {
//         for (int thread = 0; thread < threads; ++thread) {
//             int start_idx = block * nodes_per_block + thread * nodes_per_thread;
//             int end_idx = std::min(start_idx + nodes_per_thread, n_nodes);

//             // Process the assigned nodes for this thread
//             for (int idx = start_idx; idx < end_idx; ++idx) {
//                 // Perform computation on vertices.x[idx] and vertices.y[idx]
//                 // For example, you can compute some function of x and y here
//             }
//         }
//     }


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