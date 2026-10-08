//Christian Rodriguez
//CMPS 2010
//Lab 8
//3-23-23
#include <iostream>

using namespace std;

const double PENNY_VALUE   = 0.01,
             NICKEL_VALUE  = 0.05,
             DIME_VALUE    = 0.10,
             QUARTER_VALUE = 0.25;
int main(){
    int pennyQuantity,
        nickelQuantity,
        dimeQuantity,
        quarterQuantity;
    double total = 0.0;

    cout << "------------------------------------\n";
    cout << "|    WELCOME TO THE MONEY GAME!    |\n";
    cout << "|TRY TO LAND BETWEEN $1.00 & $2.00!|\n";
    cout << "------------------------------------\n";

    // penny function
    cout << "HOW MANY PENNYS?: ";
    cin >> pennyQuantity;

    //check to make sure penny quantity is not negative
    while(pennyQuantity < 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> pennyQuantity;
    }
    total += (pennyQuantity*PENNY_VALUE);

    //nickel function
    cout << "HOW MANY NICKELS?: ";
    cin >> nickelQuantity;

    while(nickelQuantity < 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> nickelQuantity;
    }
    total += (nickelQuantity*NICKEL_VALUE);

    //dime function
    cout << "HOW MANY DIMES?: ";
    cin >> dimeQuantity;

    while(dimeQuantity < 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> dimeQuantity;
    }
    total += (dimeQuantity*DIME_VALUE);

    //quarter function
    cout << "HOW MANY QUARTERS?: ";
    cin >> quarterQuantity;

    while(quarterQuantity < 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> quarterQuantity;
    }
    total += (quarterQuantity*QUARTER_VALUE);

    //determine result 
    if(total >= 1.00 && total <= 2.00){
        cout << "CONGRADULATIONS! YOU LANDED BETWEEN $1.00 AND $2.00.\n";
        cout << "Your total is $" << total << endl;}
    else if(total > 2.00)
        cout << "YOU LOSE! $" << total << " is greater than $2.00.\n";
    else if(total < 1.00)
        cout << "YOU LOSE! $" << total << " is less than $1.00.\n";

    return 0;
}
