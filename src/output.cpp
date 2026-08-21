#include "output.hpp"
#include <fstream>
#include <cstdint>

int write_mandle(Vertex<double> vertices, std::vector<double> modz) 
{
    std::ofstream file("mandlebrot.txt");

    int n = 0;
    for (int i = 0; i < vertices.nx; i++) {
        for (int j = 0; j < vertices.ny; j++) {
            file << vertices.x[i] << " " << vertices.y[j] << " " << modz[n] << std::endl;
            n++;
        }
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
