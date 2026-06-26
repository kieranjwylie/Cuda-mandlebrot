cmake_minimum_required(VERSION 3.18)
project(sierpinski LANGUAGES CXX CUDA)

set(CMAKE_CUDA_STANDARD 14)

set (files 
    cli.cpp
    cli.hpp
    complex.hpp
    data.hpp
    grid.cpp
    grid.hpp
    main.cpp
    mandle.cu
    mandle.cuh
    output.cpp
    output.hpp
)

add_executable(mandle ${files})


#target_compile_features(mandle PRIVATE cxx_std_23)
