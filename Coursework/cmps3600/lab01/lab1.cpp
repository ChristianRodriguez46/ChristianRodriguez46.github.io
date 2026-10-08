// Author: Christian ROdriguez
// lab-1
// Created date: 8/28/2025

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string name;
    cout << "Enter your name: ";
    cin >> name;
    
    int number;
    cout << "Enter your number: ";
    cin >> number;

    ofstream fout("log");
    if (fout.fail()) {
        cerr << "ERROR: opening output file." << endl;
        exit(0);
    }
    fout << name << endl;
    int sum;
    for (int i=1; i <= number; ++i)
        sum += i;
    fout << "summation from 1 to " << number << " is " << sum << endl;
    fout.close();
    return 0;
}
