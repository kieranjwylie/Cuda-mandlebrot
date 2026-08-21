#pragma once
#include "data.hpp"
#include <cuda_runtime.h>

int mandle(Vertex<double> vertices, int blocks, int threads, int its, std::vector<double> & h_modz, std::vector<int> & vertices_per_thread, std::vector<int> & start_points) ;
int output_device_props();


class Timer_Cuda
{
    private:
        cudaEvent_t start, stop;

    public:
        float time_elapsed;

    void start_timer() {
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start);
    }

    void end_timer() {
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&time_elapsed, start, stop);
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
    }

};