#include "output.hpp"
#include <fstream>


int write_mandle(Vertex<double> vertices, std::vector<double> modz) 
{
    std::ofstream file("mandlebrot.txt");

    for (int i = 0; i < vertices.nv ; i++) {
        file << vertices.x[vertices.xidx[i]] << " " << vertices.y[vertices.yidx[i]]
             << " " << modz[i] << std::endl;
    }
    return 0;
}

int write_mandle_bin(Vertex<double> vertices, std::vector<double> modz) 
{
    std::ofstream file("mandlebrot.bin", std::ios::binary);

    uint64_t nx = vertices.x.size();
    uint64_t ny = vertices.y.size();
    uint64_t nv = modz.size();

    file.write(reinterpret_cast<const char*>(&nx), sizeof(nx));
    file.write(reinterpret_cast<const char*>(&nx), sizeof(ny));
    file.write(reinterpret_cast<const char*>(&nv), sizeof(nv));
    file.write(reinterpret_cast<const char*>(vertices.x.data()), vertices.nx*sizeof(double));
    file.write(reinterpret_cast<const char*>(vertices.y.data()), vertices.ny*sizeof(double));
    file.write(reinterpret_cast<const char*>(modz.data()), vertices.nv*sizeof(double));

    return 0;
}
