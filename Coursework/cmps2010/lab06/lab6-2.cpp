//Christian Rodriguez
//Lab 6-1
//CMPS 2010
//3/0/23

#include <iostream>
#include <string>

using namespace std;

void printNames(int count);
string genFirstName();
string genLastName();

int main(int argc, char *argv[]){

    // SEED RANDOM NAME GENERATOR
    unsigned int seed = time(0);
    srand(seed);
    
    if(argc == 1){
        printNames(10);
    }else{
        int numInput = atoi(argv[1]);
        printNames(numInput);
    }


}

void printNames(int count){

    for(int i = 0 ; i <= count; i++){
        cout << genFirstName() << " " << genLastName() << endl;
    }
}

string genFirstName(){

    string RandomF;
    string fName[10] = {"Bob", "Mc", "Jerry", "Tyrone", "Ben", "Anna", "Buster", "Chase", "Buck", "Ash" };

        RandomF = fName[rand()%10];
    return RandomF;
  
}

string genLastName(){
    
    string RandomL;
    string lName[10] = {"Lovin", "Borshin", "Cherry", "Cox", "Nekkid", "Hull",
        "McCrap", "Burns", "Stroker", "Rodriguez"};
   
        RandomL = lName[rand()%10];
    return RandomL;
}
