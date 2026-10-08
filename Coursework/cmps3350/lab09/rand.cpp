#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// rand() return a number between 0 and RAND_MAX
const int times = 10000000;
int main ()
{   
    // srand(2)
    //  0 and NULL do the same thing
    srand(time(0));
    int arr[10];
    int n = 0;
    for (int k=0; k<times; k++) {
        for (int i=0; i<10; i++)
            arr[i] = rand() % 39 + 1;
        if (arr[3] !=6 && arr[4] == 6 && arr[5] == 6)
            n++;
        // for (int i=0; i<10; i++)
        //     cout << arr[i] << " ";
        // cout << endl;
    }
    cout << (double)n / (double)times << endl;
    return 0;
}