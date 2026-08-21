#include "mpi_utils.hpp"
#include "data.hpp"

int mandle(Parallel_info comms, Vertex<double> vertices, const int its, std::vector<double> &global_modz, const std::vector<int> &vertices_per_thread, const std::vector<int> & start_points);

