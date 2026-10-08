//Christian Rodriguez
//Final
//CMPS 2010
//05/17/2023
#include <iostream>
#include <fstream>
#include <string>
#include "Restaurant.h"
using namespace std;

void outputReviews(Restaurant arr[], int size);
int main(){
    int size;
    //introduction
    cout << "****************************************************\n";
    cout << "* Welcome to the Restaurant Review Program (0_0)_/ *\n";
    cout << "****************************************************\n\n";
    // the double \n is to skip two lines. it saves time
    cout << "How many restaurant would you like to review? ";
    cin >> size;

    cout << endl;

    //dynamic array
    Restaurant* rArr = new Restaurant[size];
    // for loop to input information on restaurant
    for(int i = 0; i < size; i++){
        string name, type, style;
        unsigned short numLocations;
        float score;

        cout << "Please enter the information for the restaurant " << (i + 1) << ":\n";

        cin.ignore();

        cout << "Name: ";
        getline(cin, name);
        rArr[i].setName(name);

        cout << "Type: ";
        getline(cin, type);
        rArr[i].setType(type);

        cout << "Style: ";
        getline(cin, style);
        rArr[i].setStyle(style);

        cout << "Number of Locations: ";
        cin >> numLocations;
        rArr[i].setNumLocations(numLocations);
        
        cout << "Rate the restaurant 0 out of 5: ";
        cin >> score;
        rArr[i].setScore(score);

    }
    //Call the outputReview function
    outputReviews(rArr, size);
    //delete the dynamically allocated memory
    delete[] rArr;

}
//need fstream to open and close "reviews.csv"
void outputReviews(Restaurant arr[], int size) {
    ofstream outFile;
    outFile.open("reviews.csv");

    for(int i = 0; i < size; i++) {
        outFile << arr[i].toCSV() << endl;
    }

    outFile.close();
}
