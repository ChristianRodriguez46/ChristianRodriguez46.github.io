// Christian Rodriguez
// 10/7/25

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void printNames(int count);
string genFirstName();
string genLastName();

int main(int argc, char *argv[]) {    
    // SEED RANDOM NAME GENERATOR
    unsigned int seed = time(0);
    srand(seed);

    if(argc<2) {
        printNames(10);
    } else {
        printNames(atoi(argv[1]));
    }
    return 0;
}

void printNames(int count){
    for(int i = 0 ; i <= count; i++){
        cout << genFirstName() << " " << genLastName() << endl;
    }
}

string genFirstName(){
    // string randf;
    string fNames[10] = {
        "Bob", "Jen", "Jackie", "Chris", "Tom",
        "Jerry", "Danny", "Timmy", "Cartmen", "bean"
    };

    return fNames[rand()%10];
}
string genLastName(){
    string lNames[10] = {
        "Rodriguez", "Stokes", "Floyd", "Rosario", "Norton",
        "Bowen", "Stuart", "peck", "Vincent", "Hardin"
    };

    return lNames[rand()%10];
}

