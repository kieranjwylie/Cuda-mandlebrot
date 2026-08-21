
#include "data.hpp"
#include "mpi_utils.hpp"

int setup_grid(Parallel_info comms, double xl, double xh, double yl, double yh, int nx, int ny, Vertex<double> & vertices, std::vector<int> vertices_per_thread, std::vector<int> start_points);
