// christian rodriguez
// CMPS 2010
// lab 8
// 3-21-2023

#include <iostream>
#include <string>
using namespace std;

//GLOBAL VARIBLES
const int FLOOR = 1,
      CHAIR = 2,
      DESK  = 3;

//PROTYPES
int* grab(int &book, int &pencil, int &paper);
void move(int* hand);
void showAll(int* hand, int &book, int &pencil, int &paper);
string show(int object);

int main(){
    int* hand = nullptr;
    int pencil = FLOOR,
        book   = FLOOR,
        paper  = FLOOR;
    int choice;
    bool loop = true;

    do{
        cout << endl;
        cout << "   What would you like to do?\n";
        cout << "   1) GRAB\n";
        cout << "   2) MOVE\n"; 
        cout << "   3) SHOW ALL\n";
        cout << "   0) QUIT\n";
        cout << endl;

        cin >> choice; 
        cout << endl;

        switch(choice){
            case 1:
                hand = grab(book, pencil, paper);
                break;
            case 2:
                move(hand);
                break;
            case 3:
                showAll(hand, book, pencil, paper);
                break;
            case 0:
                loop = false;
                break;
            default:
                cout << endl << "INVAILD OPTION\n";
        }
    }while(loop);

    return 0;
}
int* grab(int &book, int &pencil, int &paper){
    int choice;

    cout << "What would you like to grab?\n";
    cout << "----------------------------\n";
    cout << "1) Book\n";
    cout << "2) Pencil\n";
    cout << "3) Paper\n";
    cout << "----------------------------\n";

    cin >> choice;

    switch(choice){
        case 1:
            return &book;
            break;
        case 2:
            return &pencil;
            break;
        case 3:
            return &paper;
            break;
        default:
            return nullptr;
    }
}

void move(int* hand){
    if(!hand){
        cout << "You are not holding anything\n";
        return;
    }
    
    int choice;

    cout << "Where would you like to move it?\n";
    cout << "--------------------------------\n";
    cout << "1) FLOOR\n";
    cout << "2) CHAIR\n";
    cout << "3) DESk\n";
    cout << "--------------------------------\n";
    
    cin >> choice;
   
    if(choice >= FLOOR && choice <= DESK){
        *hand = choice;
    }
}

void showAll(int* hand, int &book, int &pencil, int &paper){
    cout << "++++++++++++++++++++++++++++++++++\n";
    cout << "+   HERE'S THE SITUATION, SON!!  +\n";
    cout << "++++++++++++++++++++++++++++++++++\n";
    cout << "The book is on the " << show(book) << endl;
    cout << "The pencil is on the " << show(pencil) << endl;
    cout << "The paper is on the " << show(paper) << endl;

    cout << endl;

    if(hand == &book){
        cout << "You are holding the book.\n";
    }else if(hand == &pencil){
        cout << "You are holding the pencil.\n";
    }else if(hand == &paper){
        cout << "You are holding the paper.\n";
    }else{
        cout << "You are holding nothing.\n";
    }
}

string show(int object){
    switch(object){
        case FLOOR: return "floor";   break;
        case CHAIR: return "chair";   break;
        case DESK:  return "desk";    break;
        default:    return "nothing"; break;
    }
}
