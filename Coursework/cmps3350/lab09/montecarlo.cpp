#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int TOTAL_TRIALS = 10000000;
int main() {   
    srand(time(0));
    int n = 0;

    for (int k = 0; k < TOTAL_TRIALS; k++) {
        int s1 = rand() % 39 + 1;
        int s2 = rand() % 39 + 1;
        int s3 = rand() % 39 + 1;

        if (s1 > s2) swap(s1, s2);
        if (s2 > s3) swap(s2, s3);
        if (s1 > s2) swap(s1, s2);

        // Check which column they belong to
        if ((s1 <= 15 && s2 <= 15 && s3 <= 15) || 
            (s1 >= 16 && s1 <= 30 && s2 >= 16 && s2 <= 30 && s3 >= 16 && s3 <= 30) || 
            (s1 >= 31 && s2 >= 31 && s3 >= 31)) {
            if (s2 == s1 + 1 && s3 == s2 + 1)
                n++;
        }
    }

    cout << "Number of tries: " << TOTAL_TRIALS << endl;
    cout << "Instances found: " << n << endl;
    cout << "    Probability: " << (double)n / TOTAL_TRIALS << endl;
    cout << "     1 in every: " << 1.0 / ((double)n / TOTAL_TRIALS);
    cout << " tries\n";

    return 0;
}