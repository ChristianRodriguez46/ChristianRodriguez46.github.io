/*! \file pi.cpp
 * \brief Program to calculate value of pi using integral.
 *
 * This program will numerically compute the integral of
 *
 * 4/(1+x*x)
 *
 * from 0 to 1. The value of this integral is pi -- which
 * is great since it gives us an easy way to check the answer.
 *
 * The is the original sequential program. It uses the timer
 * from the OpenMP runtime library.
 *
 * History: Written by Tim Mattson, 11/99.
  
    compile: g++ -fopenmp pi_4A.cpp -o 4a

    export OMP_NUM_THREADS=2; ./4a
    export OMP_NUM_THREADS=3; ./4a
    export OMP_NUM_THREADS=4; ./4a

*/
#include <omp.h>
#include <stdio.h>
#include <math.h>

#define MAX_THREADS 32
static long num_steps = 1000000;   // number of subintervals (N)
double step;                         // width of each subinterval (Sx)
double PI = atan(1) * 4;

int main()
{
    int i;
    double x, pi, sum = 0.0;
    double start_time, run_time;

    step = 1.0 / (double)num_steps;   // Sx = 1 / N

    start_time = omp_get_wtime();     // start timer

    double cumsum[MAX_THREADS] = { 0 };

    int acNT = 0;
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int NT = omp_get_num_threads();
        if (id == 0)
            acNT = NT;
        for(int i = id; i < num_steps; i+= NT)
        {
            double x = (i + 0.5) * step;                 // midpoint
            cumsum[id] += 4.0 / (1.0 + x * x);    // local sum
        }
    }
    for (i = 0; i < acNT; i++)
        sum += cumsum[i];

    pi = step * sum;                  // multiply by Sx to get integral

    run_time = omp_get_wtime() - start_time;  // stop timer

    printf("\n pi with %ld steps has error %lf in %lf seconds\n ",
           num_steps, fabs(pi-PI), run_time);

    return 0;
}