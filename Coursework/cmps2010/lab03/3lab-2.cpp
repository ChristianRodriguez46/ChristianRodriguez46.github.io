#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
    unsigned int seed = time(0);
    srand(seed);

    const int MIN_VALUE = -20;
    const int MAX_VALUE = 20;

    int userInput;

    int num = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;

    cout << "WELCOME TO THE GUESSING GAME!" << endl << endl << endl; 


    if(num > 0){
        cout << "The number is positive" << endl;
    }else{ 
        cout << "The number is negative" << endl;
    }

    if(num %2 == 0){
        cout << "The number is even" << endl;
    }else{ 
        cout << "The number is odd" << endl;
    }


    if(num >= -4 && num <= 4){
        cout << "The number is between -4 and 4 (inclusive)" << endl;
    }else{
        cout << "The number is less than -4 or greater than 4" << endl;
    }

    
    
    cout <<  "" << endl << endl;


    cout << "GUESS THE NUMBER!: "; cin >> userInput;


    
    cout << endl << endl;

    char ans;
    

        if(userInput != num)
        {
            cout << "YOUR WRONG ᕦ(ò_óˇ)ᕤ" << endl;
            cout << "Do you want another hint? (y/n)" << endl;
            cin >> ans;
          
           if(ans == 'y')
           {    
                    cout << "" << endl;
                    cout << "YOU LOSE!" << endl;
                    cout << "You really thought I would give you a hint?" << endl;
           }else
           {
                    cout << "Honorable but you still lose" << endl;
           }
        }
        else
        {
            cout << "Wow you actually got it" << endl;
        }

            cout << "" << endl;
            cout << "The number was " << num << "." << endl;

            return 0;
        }
