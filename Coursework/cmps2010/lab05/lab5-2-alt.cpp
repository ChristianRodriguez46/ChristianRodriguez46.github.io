//Christian Rodriguez 
//CMPS2010
//Lab5-2
//started 2-21-2023

#include <iostream>
#include <cmath>
#include <stdbool.h>
using namespace std;

void getWholeNumber(int &num1);
bool isPrime(int &num1);

int main(){
    int num1;
    getWholeNumber(num1);


    cout << isPrime(num1) << endl;

    return 0;
}

void getWholeNumber(int &num1){
    cout << "Please enter a WHOLE NUMBER: ";
    cin >> num1;
 
}

bool isPrime(int &num1){

    //if the number is 0 or 1 they are not prime numbers
    if(num1 <= 1){
        cout << "The number " << num1 << "is mot a prime number.\n" ;
        return false;
    }

    //'i' is the number of the iteration and divisble #
    for(int i = 2 ; i <= num1/2 ; i++ ){
        if (num1 % i == 0){
        cout << "The number " << num1 << "is mot a prime number.\n" ;
            return false;
        }
    
    }
        cout << "The number " << num1 << "is a prime number.\n" ;
 

    return true;
}

