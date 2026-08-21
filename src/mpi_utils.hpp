#include <mpi.h>

#pragma once
struct Parallel_info {
    int rank;
    int size;
    int boss_rank;
    bool boss;
};

int init_comms(Parallel_info &comms);

int finalise_comms();