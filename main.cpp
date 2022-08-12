#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#include "main.h"


using namespace std;

int main(int argc, char** argv)
{
    MPI_Init(&argc , &argv);
    auto comm = MPI_COMM_WORLD;

    int rank, size;
    MPI_Comm_size(comm , &size);
    MPI_Comm_rank(comm , &rank);

    auto start = MPI_Wtime();
    run(rank, size);
    auto end =  MPI_Wtime();

    if(rank == 0)
        cout << "Time took to execute " << end - start << "s" << endl;

    MPI_Finalize();
 
    //cout << "Rank " << rank << " exits" << endl;
    return 0;
}