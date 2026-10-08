//Christian Rodriguez
//Lab 6-1
//CMPS 2010
//3/7/23

#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream inputFile;
    int array[100];
    int count = 0;

    //Check for command line arguments
    if(argc > 1){
        inputFile.open(argv[1]);
    }else{
        cout << "USAGE: ./lab6-1 numbers.txt \n";
    }

    //If inputFile fails to open, throw error and close program
    if(!inputFile){
        cout << "There was an error reading the input file.\n";
        return 1;
    }

    //while loop tells program to grab number for array and increase counter
    while(inputFile >> array[count]){
        count++;
    }

    //how to print backwards ()
    for(int i = count - 1; i > -1; i--){
        cout << array[i] << endl;
    }

    double sum = 0;
    double average; 
    for(int i = count - 1; i > -1; i--){
        sum += array[i];   
    }

    average = sum/count;

    cout << "SUM: " << sum << endl;
    cout << "AVERAGE: " << average << endl;

    //Close the file
    inputFile.close();
    return 0;
}
