// g++ -pthread Lab10_Activity1.cpp -o act1

#include <iostream>
#include <thread>
using namespace std;

// Thread 1: prints numbers 1 to 10
void printNumbers()
{
    for (int number = 1; number <= 10; number++)
    {
        cout << number << " ";
    }
    cout << endl;
}

// Thread 2: prints letters A to N
void printLetters()
{
    for (char letter = 'A'; letter <= 'N'; letter++)
    {
        cout << letter << " ";
    }
    cout << endl;
}

int main()
{
    cout << "Starting both threads..." << endl;

    // Create and start both child threads
    thread numberThread(printNumbers);
    thread letterThread(printLetters);

    // Main thread waits for both child threads to finish
    numberThread.join();
    letterThread.join();

    cout << "Both threads finished." << endl;
    return 0;
}