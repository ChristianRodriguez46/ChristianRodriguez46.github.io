/*! \file   ArrayOp.cpp
 *  \brief  Array operation - general multi threaded
 *  \author Yi Zhao
 *  \date   08/26/2024
 */

#include <chrono> 
#include <thread>
#include <vector>

#include <math.h>
#include <stdio.h>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

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

/// sequential addition
void AddArray()
{
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        ArrayC[i] = cos(ArrayA[i]) + sin(ArrayB[i]);
}

/// threaded addition 
void AddArrayT(int head, int tail)
{
    for (int i = head; i < tail; i++)
        ArrayC[i] = cos(ArrayA[i]) + sin(ArrayB[i]);
}

void Process(int numThread = 0, int numRun = 10)
{
    double etSum = 0;
    for (int run = 1; run <= numRun; run++)
    {
        if (numThread <= 0)
        {
            auto t1 = high_resolution_clock::now();
            AddArray();
            auto t2 = high_resolution_clock::now();
            duration<double, std::milli> dif = t2 - t1;
            double etCur = dif.count();
            etSum += etCur;
            printf("  run = %2d  ET = %.3lf ms\n", run, etCur);
        }
        else
        {
            auto t1 = high_resolution_clock::now();
            std::vector<std::thread*> workers;
            for (int i = 0; i < numThread; i++)
            {
                std::thread* current = new std::thread(AddArrayT, i * MAX_ARRAY_SIZE / numThread,
                    (i + 1) * MAX_ARRAY_SIZE / numThread);
                workers.push_back(current);
            }
            for (int i = 0; i < numThread; i++)
            {
                if (workers[i]->joinable())
                    workers[i]->join();
            }
            auto t2 = high_resolution_clock::now();
            duration<double, std::milli> dif = t2 - t1;
            double etCur = dif.count();
            etSum += etCur;
            printf("  run = %2d  ET = %.3lf ms\n", run, etCur);
        }
    }
    double etAvg = etSum / numRun;
    printf("  AVG  ET = %.3lf ms\n", etAvg);
}

int main(int argc, char* argv[])
{
    int numRun = 10;
    int numThread = 0;
    if (argc > 1)
        numThread = atoi(argv[1]);
    if (numThread <= 0)
        numThread = 0;
    ClearAll();
    InitArray();
    printf("\nnumThread = %d  numRun = %d\n", numThread, numRun);
    Process(numThread, numRun);
    return 0;
}
