// This program reads data from a file.
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cctype>
using namespace std;

int main(int argc, char *argv[])
{
    ifstream inputFile;
    ofstream outputFile;
    char let;

    // Check for command line arguments
    if(argc > 2){
        inputFile.open(argv[1]);
        outputFile.open(argv[2]);
    }else{
        cout << "USAGE: ./lab5-1 <input_file> <output_file> \n";
        return 1;
    }

    // If inputFile fails to open, throw error and end program
    if(!inputFile){
        cout << "There was an error reading the input file." << endl;
        return 1;
    }else if(!outputFile){
        cout << "Could not open output file" << endl;
        return 1;
    }

    //input.get(let/letter): telling program to grab letter from inputfile 
    while(inputFile.get(let)){

        //checks if letter is lowercase if so then change to upper
        if(islower(let)){
            let = toupper(let);
        }
  
        //checks if letter is a vowel if so, move to next letter
        if(let == 'A' || let == 'E' || let == 'I' || let == 'O' || let == 'U'){
            continue;
        }
       
        //checks if there is a space then change to underscore
        if (let == ' '){
            let = '_';
        }

        outputFile.put(let);
    }

    // Close the files.
    inputFile.close();
    outputFile.close();
    return 0;
}




