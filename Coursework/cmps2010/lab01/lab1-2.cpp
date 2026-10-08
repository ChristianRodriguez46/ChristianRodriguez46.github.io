// christian Rodriguez
// CMPS2010
// Lab1-2
// 1.27.2023



#include <iostream>
using namespace std;

int main (){
    int input1, input2;
    double num1, num2;

    input1=1337;
    input2=42;
    num1=86.7;
    num2=5.309;

    cout << "    ** Welcome to the Math Machine! **  " << endl << endl; 

    cout << "The first integer is " << input1 << endl;
    cout << "The second integer is " << input2 << endl << endl;

    cout << "The sum is " <<input1+input2 << endl;
    cout << "The difference is " << input1-input2 << endl;
    cout << "The product is " << input1*input2 << endl;
    cout << "The quotient is " << input1/input2 << " with a remainder of " << input1%input2 << endl << endl;

    cout << "The first double is " << num1 << endl;
    cout << "The second double is " << num2 << endl << endl;
    
    cout << "The sum is " << num1+num2 << endl;
    cout << "The difference is " << num1-num2 << endl;
    cout << "The product is " << num1*num2 << endl;
    cout << "The quotient is " << num1/num2 << endl;


    return 0;
}
    
