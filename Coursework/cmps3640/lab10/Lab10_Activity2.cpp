// g++ -pthread Lab10_Activity2.cpp -o act2

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

const int N = 100000000;  // array size: 100 million elements

int A[N], B[N], C[N];    // A and B are inputs, C is the result

// Thread function: adds elements from startIndex up to (but not including) endIndex
void addSection(int startIndex, int endIndex)
{
    for (int i = startIndex; i < endIndex; i++)
    {
        C[i] = A[i] + B[i];
    }
}

// Sequential version for comparison
void addSequential()
{
    for (int i = 0; i < N; i++)
    {
        C[i] = A[i] + B[i];
    }
}

int main()
{
    // Initialize arrays
    for (int i = 0; i < N; i++)
    {
        A[i] = 1;
        B[i] = 2;
    }

    int halfPoint = N / 2;

    // ── Parallel addition ─────────────────────────────────────────────────
    auto parallelStart = chrono::high_resolution_clock::now();

    // Thread 1 handles the first half  [0 .. halfPoint)
    // Thread 2 handles the second half [halfPoint .. N)
    thread firstHalfThread(addSection, 0, halfPoint);
    thread secondHalfThread(addSection, halfPoint, N);

    firstHalfThread.join();
    secondHalfThread.join();

    auto parallelEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> parallelTime = parallelEnd - parallelStart;

    // ── Sequential addition ───────────────────────────────────────────────
    auto sequentialStart = chrono::high_resolution_clock::now();

    addSequential();

    auto sequentialEnd = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> sequentialTime = sequentialEnd - sequentialStart;

    // ── Print results ─────────────────────────────────────────────────────
    cout << "Array size        : " << N << " elements" << endl;
    cout << "Parallel time     : " << parallelTime.count()   << " ms" << endl;
    cout << "Sequential time   : " << sequentialTime.count() << " ms" << endl;
    cout << "Speedup (seq/par) : " << sequentialTime.count() / parallelTime.count() << "x" << endl;

    return 0;
}