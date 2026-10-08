/*! \file   ArrayOpOMP.cpp
 *  \brief  Array operation - OpenMP version
 *  \author Yi Zhao
 *  \date   09/02/2024
 */

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE  20000000

double ArrayA[MAX_ARRAY_SIZE];
double ArrayB[MAX_ARRAY_SIZE];
double ArrayC[MAX_ARRAY_SIZE];

void ClearAll()
{
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        ArrayA[i] = ArrayB[i] = ArrayC[i] = 0;
    }
}

void InitArray()
{
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        ArrayA[i] = rand();
        ArrayB[i] = rand();
    }
}

int main(int argc, char* argv[])
{
    int numThreads = 4, actThreads = 0;
    double start_time, run_time;
    if (argc > 1)
        numThreads = atoi(argv[1]);
    if (numThreads <= 0)
        numThreads = 1;
    ClearAll();
    InitArray();
    printf("\nnumThreads = %d\n ", numThreads);

    start_time = omp_get_wtime();   // this is the timer we want to use when using OpemMP

    omp_set_num_threads(numThreads);
    #pragma omp parallel
    {
        int id, NT;
        id = omp_get_thread_num();
        NT = omp_get_num_threads();
        if (id == 0)
            actThreads = NT;
        
        int start = id * MAX_ARRAY_SIZE / NT;               // START
        int end = (id+1) * MAX_ARRAY_SIZE / NT;             // END

        for (int i = start; i < end; i += NT)
        {
            ArrayC[i] = cos(ArrayA[i]) + sin(ArrayB[i]);
        }
    }

    run_time = omp_get_wtime() - start_time;
    printf("\nactThreads = %d  ET = %lf seconds\n ", actThreads, run_time);

    return 0;
}
