// g++ -fopenmp par_histogram.cpp -o par_hist && ./par_hist

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int main()
{
    const int N = 100000; //100,000
    int X[N];
    int hist[10] = {0};

    // Declare an array of locks — one per bin
    omp_lock_t hist_locks[10];

    // Randomly initialize values 0-9
    srand(time(0));
    for (int i = 0; i < N; i++)
        X[i] = rand() % 10;

    // Initialize each bin's lock
    for (int i = 0; i < 10; i++)
        omp_init_lock(&hist_locks[i]);

    // start time for histogram computation
    double start = omp_get_wtime();

    #pragma omp parallel for
        for (int i = 0; i < N; i++)
        {
            omp_set_lock(&hist_locks[X[i]]);   // lock only the bin being updated
            hist[X[i]]++;
            omp_unset_lock(&hist_locks[X[i]]); // release that bin's lock
        }

    // end time for histogram comp
    double end = omp_get_wtime();

    // Destroy each bin's lock
    for (int i = 0; i < 10; i++)
        omp_destroy_lock(&hist_locks[i]);
 
    // Print histogram results
    cout << "=== Parallel Histogram (OpenMP Locks) ===" << endl;
    cout << "Threads used: " << omp_get_max_threads() << endl;
    for (int i = 0; i < 10; i++)
        cout << "Bin " << i << ": " << hist[i] << endl;
 
    cout << "\nParallel Time: " << (end - start) << " seconds" << endl;

    return 0;
}