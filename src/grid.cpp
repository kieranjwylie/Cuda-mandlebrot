#include <vector>
#include "grid.hpp"

void set_arr(std::vector<double> & arr, int n, double l, double d)
{
    for (int i = 0; i < n; i++) {
        arr[i] = l + i * d;
    }
    return;
}

int setup_grid(double xl, double xh, double yl, double yh, int nx, int ny, Vertex<double> & vertices)
{
    double dx = (xh - xl) / nx;
    double dy = (yh - yl) / ny;

    int nv = ny*nx;

    vertices.x.resize(nx);
    vertices.y.resize(ny);
    vertices.idx.resize(nv);
    vertices.xidx.resize(nv);
    vertices.yidx.resize(nv);

    vertices.nx = nx;
    vertices.ny = ny;
    vertices.nv = nv;

    set_arr(vertices.x, nx, xl, dx);
    set_arr(vertices.y, ny, yl, dy);

    int i = 0;
    for (int n = 0; n < nx; n++) {
        for (int m = 0; m < ny; m++) {
            vertices.idx[i] = i;
            vertices.xidx[i] = n;
            vertices.yidx[i] = m;
            i++;
        }
    }

    return 0;
}
