//Christian Rodriguez
//Lab 2-2
//CMPS 2010
// 2.3.2023

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){
  double num1;


  cout << "Please enter a decimal number: ";
        cin >> num1;
  cout << " " << endl;


  cout << right << showpoint << setprecision(7);


  cout << "SIN: ";
  cout << right << setw(45) << sin(num1) << endl;

  cout << "COSINE: ";
  cout << right << setw(42) << cos(num1) << endl;

  cout << "TANGENT: ";
  cout << right << setw(40) << tan(num1) << endl;

  cout << "EXPONENT: ";
  cout << right << setw(39) << exp(num1)  << endl;

  cout << "LOG: ";
  cout << right << setw(45) << log(num1) << endl;

  cout << "SQUARE ROOT: ";
  cout << right << setw(37) << sqrt(num1) << endl;
  
  return 0;
}
