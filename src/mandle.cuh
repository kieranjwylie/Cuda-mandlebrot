#pragma once
#include "data.hpp"

int mandle(Vertex<double> vertices, int blocks, int threads, int its, std::vector<double> & h_modz, std::vector<int> & vertices_per_thread);
int output_device_props();
