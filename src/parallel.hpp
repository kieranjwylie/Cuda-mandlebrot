#include "data.hpp"


// For a gpu
void distribute_nodes(const int n_nodes, std::vector<int> & vertices_per_thread, std::vector<int> & start_points, int threads);

void output_vertex_dist(const int n_nodes, std::vector<int> vertices_per_thread, std::vector<int> & start_points, int threads);