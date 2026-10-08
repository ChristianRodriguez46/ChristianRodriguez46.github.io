// compile g++ -fopenmp pi_4B.cpp -o 4b
/* run program

    export OMP_NUM_THREADS=2; ./4b
    export OMP_NUM_THREADS=3; ./4b
    export OMP_NUM_THREADS=4; ./4b

*/

#include <omp.h>
#include <stdio.h>
#include <math.h>

#define MAX_THREADS 32
static long num_steps = 1000000;
double step;
double PI = atan(1) * 4;

int main()
{
    int i;
    double x, pi, sum = 0.0;
    double start_time, run_time;

    step = 1.0 / (double)num_steps;

    start_time = omp_get_wtime();

    double cumsum[MAX_THREADS] = {0.0};
    int acNT = 0;

#pragma omp parallel
    {
        int id = omp_get_thread_num();
        int NT = omp_get_num_threads();

        if (id == 0)
            acNT = NT;

        long start = id * num_steps / NT;               // START
        long end = (id+1) * num_steps / NT;             // END

        if (id == NT - 1)
            end = num_steps;                         // last thread gets remainder

        // approach (b): each thread sums its own segment start..end-1
        for (int j = start; j < end; j++)
        {
            double x = (j + 0.5) * step;                    // midpoint
            cumsum[id] += 4.0 / (1.0 + x * x);       // local sum
        }
    }

    for (i = 0; i < acNT; i++)
        sum += cumsum[i];

    pi = step * sum;

    run_time = omp_get_wtime() - start_time;

    printf("\n pi with %ld steps has error %lf in %lf seconds\n ",
           num_steps, fabs(pi - PI), run_time);

    return 0;
}
