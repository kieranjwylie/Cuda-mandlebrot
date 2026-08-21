#include <vector>
#include "grid.hpp"

void set_arr(std::vector<double> & arr, int n, double l, double d)
{
    for (int i = 0; i < n; i++) {
        arr[i] = l + i * d;
    }
    return;
}

// Only a single processor needs to do this
int setup_grid(Parallel_info comms, double xl, double xh, double yl, double yh, int nx, int ny, Vertex<double> & vertices, std::vector<int> vertices_per_thread, std::vector<int> start_points)
{
    double dx = (xh - xl) / nx;
    double dy = (yh - yl) / ny;

    int nv = ny*nx;


    vertices.x.resize(nx);
    vertices.y.resize(ny);

    vertices.nx = nx;
    vertices.ny = ny;
    vertices.nv = nv;

    set_arr(vertices.x, nx, xl, dx);
    set_arr(vertices.y, ny, yl, dy);

    vertices.xidx.resize(vertices_per_thread[comms.rank]);
    vertices.yidx.resize(vertices_per_thread[comms.rank]);

    int i = 0;
    int count_on_thread = 0;
    int global_id;
    for (int n = 0; n < nx; n++) {
        for (int m = 0; m < ny; m++) {

            if ( i >= start_points[comms.rank] && i < start_points[comms.rank] + vertices_per_thread[comms.rank]) {
                vertices.xidx[count_on_thread] = n;
                vertices.yidx[count_on_thread] = m;
                count_on_thread ++;
            }
            i++;
        }
    }

    return 0;
}
