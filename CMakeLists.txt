cmake_minimum_required(VERSION 3.18)
project(sierpinski LANGUAGES CXX CUDA)

set(CMAKE_CUDA_STANDARD 14)

set (files 
    src/cli.cpp
    src/cli.hpp
    src/complex.hpp
    src/data.hpp
    src/grid.cpp
    src/grid.hpp
    src/main.cpp
    src/mandle.cu
    src/mandle.cuh
    src/output.cpp
    src/output.hpp
)

add_executable(mandle ${files})


#target_compile_features(mandle PRIVATE cxx_std_23)
