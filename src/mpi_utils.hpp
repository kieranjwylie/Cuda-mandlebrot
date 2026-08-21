#include <mpi.h>

#pragma once
struct Parallel_info {
    int rank;
    int size;
    bool boss;
};

int init_comms(Parallel_info &comms);

int finalise_comms();