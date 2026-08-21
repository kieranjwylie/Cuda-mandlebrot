#include "complex.hpp"
#include "mandle.cuh"
#include <iostream>
#include <cuda.h>
#include <cuda_runtime.h> 
#include <curand_kernel.h>


#define CUDA_CHECK(err) cudaCheck(err)

void cudaCheck(cudaError_t err) {
  if (err != cudaSuccess) {
    std::cerr << "CUDA Error: " << cudaGetErrorString(err) << " (" << static_cast<int>(err) << ")"
              << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

__device__ void mandlebrot_calc(const Complex<double>& c, const int its, double& modz) {
    Complex<double> z(0.0, 0.0);
    for (int i = 1; i < its; i++) { 
        z = z*z + c;
        if (z.mod() > 2.0){
          modz = 0.0;
          return;
        }
    }
    modz = z.mod();
}

__global__ void complex_loop(const double* x, const double* y, const int* xidx, const int* yidx, const int its, double* modz, const int* vertices_per_thread)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int num_vertices = vertices_per_thread[idx];

    double local_modz = -1.0; // Initialize local_modz to -1.0 for each thread

    for (int i_vertex = 0; i_vertex < num_vertices; ++i_vertex) {
        int vertex_idx = idx + i_vertex;
        Complex<double> c(x[xidx[vertex_idx]], y[yidx[vertex_idx]]);
        mandlebrot_calc(c, its, local_modz);

        modz[vertex_idx] = local_modz;
    }

    return;
}

int mandle(Vertex<double> vertices, int blocks, int threads, int its, std::vector<double> & h_modz, std::vector<int> & vertices_per_thread) 
{
    double *d_x, *d_y, *d_modz;
    int *d_xidx, *d_yidx, *d_vertices_per_thread;

    h_modz.resize(vertices.nv);
    for (int i = 0; i < vertices.nv; i++) {
      h_modz[i] = -1.0;
    }

    // Send problem info to the gpu
    CUDA_CHECK(cudaMalloc(&d_x, vertices.nx * sizeof(double) ));
    CUDA_CHECK(cudaMalloc(&d_y, vertices.ny * sizeof(double) ));
    CUDA_CHECK(cudaMalloc(&d_xidx, vertices.nv * sizeof(int) ));
    CUDA_CHECK(cudaMalloc(&d_yidx, vertices.nv * sizeof(int) ));
    CUDA_CHECK(cudaMalloc(&d_vertices_per_thread, blocks * threads * sizeof(int)));
    CUDA_CHECK(cudaMalloc(&d_modz, vertices.nv * sizeof(double) ));

    CUDA_CHECK(cudaMemcpy(d_x, vertices.x.data(), vertices.nx * sizeof(double), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_y, vertices.y.data(), vertices.ny * sizeof(double), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_xidx, vertices.xidx.data(), vertices.nv * sizeof(int), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_yidx, vertices.yidx.data(), vertices.nv * sizeof(int), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_vertices_per_thread, vertices_per_thread.data(), blocks * threads * sizeof(int), cudaMemcpyHostToDevice));

    // Execute
    complex_loop<<<blocks,threads>>>(d_x, d_y, d_xidx, d_yidx, its, d_modz, d_vertices_per_thread);

    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess){
      std::cout << "Failure on the GPU" << std::endl;
    }

    CUDA_CHECK(cudaMemcpy(h_modz.data(), d_modz, vertices.nv * sizeof(double), cudaMemcpyDeviceToHost));


    return 0;
}

int output_device_props() {
  int device;
  cudaGetDevice(&device);

  cudaDeviceProp prop;
  CUDA_CHECK(cudaGetDeviceProperties(&prop, device));

  std::cout << "Device Name: " << prop.name << std::endl;
  std::cout << "Max Threads per Block: " << prop.maxThreadsPerBlock << std::endl;

  // Maximum threads per block in each dimension (x, y, z)
  std::cout << "Max threads per block dimension: " << prop.maxThreadsDim[0] << " x "
            << prop.maxThreadsDim[1] << " x " << prop.maxThreadsDim[2] << std::endl;

  // Maximum number of blocks in the grid (x, y, z)
  std::cout << "Max grid size (blocks per dimension): " << prop.maxGridSize[0] << " x "
            << prop.maxGridSize[1] << " x " << prop.maxGridSize[2] << std::endl;

  return 0;
}
