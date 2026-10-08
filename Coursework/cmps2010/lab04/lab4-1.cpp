//Christian Rodriguez
//2.15.2023
//CMPS2010
//Lab 4

#include <iostream>
using namespace std;

//total += qRequested*b_price;
const double B_price = 0.75,
      A_price = 1.00,
      O_price = 1.25;
int main(){

    int appleQuantity = 20; 
    int bananaQuantity = 30;
    int orangeQuantity = 10;
    int option;
    int qRequested;

    double total = 0.0;
    bool quit = false;

    while (!quit){

        cout << endl; 
        cout << "---------------------\n";
        cout << "   It's Fruit Time! Choose An Option!  \n";
        cout << "---------------------\n";

        cout << "CURRENT INVENTORY: \n";
        cout << "1) Apples:            " << appleQuantity << endl;
        cout << "2) Bananas:           " << bananaQuantity << endl;
        cout << "3) Oranges:           " << orangeQuantity << endl;
        cout << "4) quit    " << endl;

        cout << endl;

        cout << "Please Choose a line item: ";
        cin >> option;

        cout << endl;

        while( option < 1 || option > 4 )
        {
            cout <<  "Invalid option ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> option;
        }  

        if(option != 4){
            cout << "Please enter desired quantity: ";
            cin >> qRequested;
        }

        cout << endl << endl;

        switch(option)
        {
            case 1:
                while( qRequested < 1 || qRequested > appleQuantity ){
                    cout << "invalid number!\ntry again: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin >> qRequested;
                }
                appleQuantity -= qRequested;
                total += qRequested * A_price;
                cout << "There are " << appleQuantity 
                     << " apples remaining." << endl;
                break;
            case 2:
                while( qRequested < 1 || qRequested > bananaQuantity ){
                    cout << "Invalid number!\nTry again: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin >> qRequested;
                }
                bananaQuantity-= qRequested;
                total += qRequested * B_price;
                cout << "There are " << bananaQuantity << " bananas remaining." << endl;
                break;
            case 3:
                while( qRequested < 1 || qRequested > orangeQuantity ){
                    cout << "invalid number!\ntry again: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin >> qRequested;
                }
                orangeQuantity-= qRequested;
                total += qRequested * O_price;
                cout << "There are " << orangeQuantity << " oranges remaining." << endl;
                break;
            case 4:
                cout << "THANKS FOR SHOPPING\n";
                quit = true;
                break;
            default:
                cout << "Invalid option!";
        }
    }

    cout << "You owe $"  << total << endl;

    return 0;
}
