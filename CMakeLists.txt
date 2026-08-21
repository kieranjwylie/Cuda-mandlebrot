cmake_minimum_required(VERSION 3.18)
project(mandlebrot LANGUAGES CXX CUDA)

set(CMAKE_CUDA_STANDARD 14)

find_package(MPI REQUIRED)

set (files 
    src/json_parser/parse_json.cpp
    src/json_parser/parse_json.hpp
    src/json_parser/settings.hpp
    src/cli.cpp
    src/cli.hpp
    src/complex.hpp
    src/data.hpp
    src/grid.cpp
    src/grid.hpp
    src/main.cpp
    src/mandle.cpp
    src/mandle.hpp
    src/mpi_utils.cpp
    src/mpi_utils.hpp
    src/output.cpp
    src/output.hpp
    src/parallel.cpp
    src/parallel.hpp
)

add_executable(mandle ${files})
target_link_libraries(mandle PRIVATE MPI::MPI_CXX)
#target_compile_features(mandle PRIVATE cxx_std_23)
