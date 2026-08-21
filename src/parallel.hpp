#include "data.hpp"


// For a gpu
void distribute_nodes(Vertex<double> vertices, std::vector<int> & vertices_per_thread, std::vector<int> & start_points, int threads);

void output_vertex_dist(Vertex<double> vertices, std::vector<int> vertices_per_thread, std::vector<int> & start_points, int threads);