#include<vector>

#pragma once
template <typename T>
struct Vertex
{
    std::vector<T> x;
    std::vector<T> y;

    std::vector<int> idx;
    std::vector<int> yidx;
    std::vector<int> xidx;

    int nx, ny, nv;
};
