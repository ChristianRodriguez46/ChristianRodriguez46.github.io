// g++ -pthread Lab10_Activity3.cpp -o act3

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

const int N = 1000000;  // array size: 1 million elements
const int NUM_THREADS = 4;        // number of worker threads

int A[N];              // input array
long long globalSum = 0;  // shared result — protected by mutex
mutex sumMutex;           // guards globalSum from simultaneous writes

// Thread function: sums elements from startIndex up to (but not including) endIndex
void sumSection(int startIndex, int endIndex)
{
    // Compute a local partial sum first (no mutex needed — local to this thread)
    long long localPartialSum = 0;
    for (int i = startIndex; i < endIndex; i++)
    {
        localPartialSum += A[i];
    }

    // Lock mutex before adding partial sum to the shared globalSum
    sumMutex.lock();
    globalSum += localPartialSum;
    sumMutex.unlock();
}

int main()
{
    // Initialize array with 1s (expected sum = N)
    for (int i = 0; i < N; i++)
    {
        A[i] = 1;
    }

    int sectionSize = N / NUM_THREADS;  // elements per thread

    // Create all four threads in a single for-loop
    thread workerThreads[NUM_THREADS];

    for (int threadIndex = 0; threadIndex < NUM_THREADS; threadIndex++)
    {
        int startIndex = threadIndex * sectionSize;

        // Last thread takes any remaining elements
        int endIndex = (threadIndex == NUM_THREADS - 1) ? N : startIndex + sectionSize;

        workerThreads[threadIndex] = thread(sumSection, startIndex, endIndex);
    }

    // Wait for all threads to finish
    for (int threadIndex = 0; threadIndex < NUM_THREADS; threadIndex++)
    {
        workerThreads[threadIndex].join();
    }

    cout << "Array size    : " << N           << endl;
    cout << "Num threads   : " << NUM_THREADS << endl;
    cout << "Computed sum  : " << globalSum   << endl;
    cout << "Expected sum  : " << N           << endl;
    cout << "Result correct: " << (globalSum == N ? "YES" : "NO") << endl;

    return 0;
}