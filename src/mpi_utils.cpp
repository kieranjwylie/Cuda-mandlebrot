#include "mpi_utils.hpp"

int init_comms(Parallel_info &comms) {
    int ierr;

    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &comms.rank);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &comms.size);
    
    if (comms.rank == 0) {
        comms.boss = true;
    } else {
        comms.boss = false;
    }

    comms.boss_rank = 0;
    return ierr;
}

int finalise_comms() {
    int ierr = MPI_Finalize();
    return ierr;
}