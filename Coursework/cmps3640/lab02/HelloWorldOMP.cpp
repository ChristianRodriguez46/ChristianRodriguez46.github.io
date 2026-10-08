/*! \file HelloWorldOMP.cpp
 * \brief Hello World program in OpenMP.
 */
#include <omp.h>
#include <stdio.h>
int main()
{
    // Change this value each run: 2, 3, 4, 6
    int NT = 6;

    omp_set_num_threads(NT);

    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf(" Hello(%d)", ID);
        printf(" World(%d)\n", ID);
    }
    return 0;
}
