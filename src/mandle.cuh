#pragma once
#include "data.hpp"


int mandle(Vertex<double> vertices, int blocks, int threads, int its, std::vector<double> & h_modz);
int output_device_props();
