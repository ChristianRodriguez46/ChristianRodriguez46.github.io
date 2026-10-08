#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int num1;
    int num2;
    char choice;
    cout << "TIME FOR MORE MATH STUFF!" << endl << endl;

    cout << "Please enter an integer: ";
    cin >> num1;
    
    cout << "Please enter another integer: ";
    cin >> num2;
    
    cout << "Please enter a single math operator: ";
    cin >> choice;

    cout << "\n";

    switch (choice)
    {
        case '+': 
            cout << num1 << "+" << num2 << "=" << num1+num2 << endl;
            break;
        case '-': 
            cout << num1 << "-" << num2 << "=" << num1-num2 << endl;
            break;
        case '*':
            cout << num1 << "*" << num2 << "=" << num1*num2 << endl;
            break;
        case '/':
            cout << num1 << "/" << num2 << "=" << num1/num2 << endl;
            break;
        case '%':
            cout << num1 << "%" << num2 << "=" << num1%num2 << endl;
            break;
        default:
            cout << "You did not enter +, -, *, /, %!\n";
    }

    return 0;
}
