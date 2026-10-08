// $ g++ -fopenmp seq_histogram.cpp -o seq_hist && ./seq_hist

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int main()
{
    const int N = 100000;
    int X[N];
    int hist[10] = {0};

    // Randomly initialize array with values 0-9
    srand(time(0));
    for (int i = 0; i < N; i++)
        X[i] = rand() % 10;

    // Measure time for histogram computation only
    double start = omp_get_wtime();

    for (int i = 0; i < N; i++)
    {
        // set lock   (not needed in serial)
        hist[X[i]]++;
        // unset lock (not needed in serial)
    }

    double end = omp_get_wtime();

    // Print histogram results
    cout << "=== Sequential Histogram ===" << endl;
    for (int i = 0; i < 10; i++)
        cout << "Bin " << i << ": " << hist[i] << endl;

    cout << "\nSequential Time: " << (end - start) << " seconds" << endl;

    return 0;
}