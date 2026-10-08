#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main (int argc, char *argv[])
{  
    srand(time(0));
    int rows = 2;
    int cols = 2;
    int carry = 0;    
    if (argc > 1)
        rows = atoi(argv[1]);
    if (argc > 2)
        cols = atoi(argv[2]);
    int count; 
    int* sumCount = new int[cols]();
    
    for (int i = 0; i < rows; i++) {
        cout << " ";
        for (int j = 0; j < cols; j++) {
            count = rand() % 10; 
            cout << count;
            sumCount[j] += count; 
        }
        cout << endl;
    }
    for (int i = 0; i < 25; i++) 
        cout << "--";
    cout << endl;
    for (int j = cols - 1; j >= 0; j--) {
        if (j != 0) {
            if (sumCount[j] >= 10) {
                carry = sumCount[j] / 10;
                sumCount[j-1] += carry;
                sumCount[j] %= 10;
            }
        }
    }
    for (int j = 0; j < cols; j++)
        cout << sumCount[j];
    cout << endl;

    delete[] sumCount;
    return 0;
}