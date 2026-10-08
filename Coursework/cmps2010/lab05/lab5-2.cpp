//Christian Rodriguez 
//CMPS2010
//Lab5-2
//Submitted 2-23-2023
//resubmited 2-27-2023
#include <iostream>
#include <cmath>
#include <stdbool.h>
using namespace std;

void getWholeNumber(int &num1);
bool isPrime(int num1);
void printFactors(int num1);

int main(){
    int num1;

    getWholeNumber(num1);

    cout << endl;

    if( isPrime(num1)){
        cout << num1 << " is prime! \n";
    }else{
        cout << num1 << " is NOT prime number! \n";
    }

    printFactors(num1);

    cout << endl;

    return 0;
}



void getWholeNumber(int &num1){
    cout << "Please enter a WHOLE NUMBER: ";
    while( !(cin >> num1) || (num1 < 0) ){
            cout << "Invalid number. Try again: ";
            cin.clear();
            cin.ignore(1000, '\n'); 
    }

}



bool isPrime(int num1){

    //if the num1ber is 0 or 1 they are not prime num1bers
    if(num1 <= 1){
        return false;
    }

    //'i' is the num1ber of the iteration and divisble #
    for(int i = 2 ; i <= num1/2 ; i++ ){
        if (num1 % i == 0){
            return false;
        }

    }

    return true;
}



void printFactors(int num1){
    
    if(num1 != 0){
        cout << "The factors of " << num1 << " are: \n";
    }else{
        cout << "The factors of " << num1 << " are: 0\n ";
    }
    
    for(int i = 1; i <= num1; ++i ) {
        if (num1 % i == 0){
            cout << i << " ";
        }
    }
}
