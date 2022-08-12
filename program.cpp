#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <string.h>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cstdlib>

#include "program.h"

using namespace std;
using namespace std::this_thread;

void run(int rank, int size)
{
    int count = 1000;
    int a = 0;
        
        int** array = (int**)malloc((count/size + 2) * sizeof(int*));
        int** arr = (int**)malloc((count/size + 2) * sizeof(int*));
        for (int i = 0; i < count/size + 2; i++)
        {
            arr[i] = (int*)malloc(count * sizeof(int));
            array[i] = (int*)malloc(count * sizeof(int));
            // cout << rank << " " << "  ";
            for (int j = 0; j < count; j++)
            {
                arr[i][j] = rand() % 2;
                if (i == 0 || j == 0 || i == (count/size + 2) - 1 || j == count - 1)
                {
                    arr[i][j] = 0;
                }

                array[i][j] = arr[i][j];
                // cout << arr[i][j] << " ";
            }
            // cout << endl;
            
        }


    int num = 0;
    int iterations = 1000;
    int tag = 1;
    MPI_Request request = MPI_REQUEST_NULL;
    MPI_Request arequest = MPI_REQUEST_NULL;
    for (int a = 0; a < iterations; a++)
    {
        if (a % 2 == 0)
        {
            if(rank < size - 1)
            {
                MPI_Issend(
                    arr[count/size], 
                    count, 
                    MPI_INT, 
                    rank+1, 
                    tag, 
                    MPI_COMM_WORLD,
                    &request);
            }

            if(rank > 0)
            {

                 MPI_Issend(
                    arr[1], 
                    count, 
                    MPI_INT, 
                    rank-1, 
                    tag, 
                    MPI_COMM_WORLD,
                    &arequest);  

                MPI_Irecv(
                    arr[0], 
                    count, 
                    MPI_INT, 
                    rank-1,  
                    tag, 
                    MPI_COMM_WORLD,
                    &request);
            }
            
            if (rank != size - 1)
            {
                MPI_Irecv(
                    arr[count/size + 1], 
                    count, 
                    MPI_INT, 
                    rank+1,  
                    tag, 
                    MPI_COMM_WORLD,
                    &arequest);
            }

            MPI_Wait(&request, MPI_STATUS_IGNORE);
            MPI_Wait(&arequest, MPI_STATUS_IGNORE);

            for (int i = 1; i < count/size + 1; i++)
            {
                for (int j = 1; j < count - 1; j++)
                {
                    if (arr[i][j - 1] == 1)
                    {
                        num++;
                    }
                    if (arr[i + 1][j - 1] == 1)
                    {
                        num++;
                    }
                    if (arr[i - 1][j] == 1)
                    {
                        num++;
                    }
                    if (arr[i][j] == 1)
                    {
                        num++;
                    }
                    if (arr[i + 1][j] == 1)
                    {
                        num++;
                    }
                    if (arr[i - 1][j + 1] == 1)
                    {
                        num++;
                    }
                    if (arr[i][j + 1] == 1)
                    {
                        num++;
                    }
                    if (arr[i + 1][j + 1] == 1)
                    {
                        num++;
                    }

                    if(arr[i][j] == 0 && (num == 3 || num == 4))
                    {
                        array[i][j] = 1;
                    }
                    else if(arr[i][j] == 1 && (num != 3 || num != 2))
                    {
                        array[i][j] = 0;
                    } 
                    arr[i][j] = array[i][j];
                    num = 0;
                }
            }    
        }
        else
        {
            if(rank < size - 1)
            {
                MPI_Issend(
                    array[count/size], 
                    count, 
                    MPI_INT, 
                    rank+1, 
                    tag, 
                    MPI_COMM_WORLD,
                    &request);
            }

            if (rank != 0)
            {
                MPI_Issend(
                    array[1], 
                    count, 
                    MPI_INT, 
                    rank-1, 
                    tag, 
                    MPI_COMM_WORLD,
                    &arequest); 
            }

            if(rank > 0)
            {
                MPI_Irecv(
                    array[0], 
                    count, 
                    MPI_INT, 
                    rank-1,  
                    tag, 
                    MPI_COMM_WORLD,
                    &request);
            }
            
            if (rank != size - 1)
            {
                MPI_Irecv(
                    array[count/size + 1], 
                    count, 
                    MPI_INT, 
                    rank+1,  
                    tag, 
                    MPI_COMM_WORLD,
                    &arequest);   
            }

            MPI_Wait(&request, MPI_STATUS_IGNORE);
            MPI_Wait(&arequest, MPI_STATUS_IGNORE);

            for (int i = 1; i < count/size + 1; i++)
            {
                for (int j = 1; j < count - 1; j++)
                {
                    if (array[i][j - 1] == 1)
                    {
                        num++;
                    }
                    if (array[i + 1][j - 1] == 1)
                    {
                        num++;
                    }
                    if (array[i - 1][j] == 1)
                    {
                        num++;
                    }
                    if (array[i][j] == 1)
                    {
                        num++;
                    }
                    if (array[i + 1][j] == 1)
                    {
                        num++;
                    }
                    if (array[i - 1][j + 1] == 1)
                    {
                        num++;
                    }
                    if (array[i][j + 1] == 1)
                    {
                        num++;
                    }
                    if (array[i + 1][j + 1] == 1)
                    {
                        num++;
                    }

                    if(array[i][j] == 0 && (num == 3 || num == 4))
                    {
                        arr[i][j] = 1;
                    }
                    else if(array[i][j] == 1 && (num != 3 || num != 2))
                    {
                        arr[i][j] = 0;
                    } 
                    arr[i][j] = array[i][j];
                    num = 0;

                }
            }    
        }  






        // cout << endl; 
        // for (int i = 0; i < count; i++)
        // {
        //     for (int j = 0; j < count; j++)
        //     {
        //         cout << arr[i][j] << " ";
        //     }
        //     cout << endl;
        // }     
    
        
    }

    // cout << endl; 
    // for (int i = 1; i < count/size + 1; i++)
    // {
    //     cout << rank << "   ";
    //     for (int j = 1; j < count - 1; j++)
    //     {
    //         cout << arr[i][j] << " ";
    //     }
    //         cout << endl;
    // }

}