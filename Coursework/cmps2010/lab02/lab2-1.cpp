// Christian Rodriguez
// lab 2-1
// CMPS 2010
//1.31.2023


#include <iostream>
#include <string>
using namespace std;

int main(){
    int num1;
    string name, occupation, adj, verb, animal, phrase;

    cout << "Enter a name: ";
    cin >> name;

    cout << "Enter an occupation ending in er: ";
    cin >> occupation;

    cout << "Enter an adjective: ";
    cin >> adj;

    cout << "Enter a verb: ";
    cin >> verb;

    cin.ignore();
    cout << "Enter a number: ";
    cin >> num1;

    cout << "Enter an animal (plural): ";
    cin >> animal;

    cin.ignore();
    cout << "Enter an excited phrase: ";
    getline(cin,phrase);

    cout << " " << endl;
    cout << " " << endl;

    cout << "This is the tale of " << name << " the " << occupation << "." << endl;
    cout << "One day " << name << " felt " << adj << " so they decided to " << verb << "." << endl;
    cout << "But right when " << name << " was about to " << verb << " they encountered a pack of " << num1 << " wild " << animal << "!" <<  endl;
    cout << name << " ran away screaming \"" << phrase << "!\"" << endl << endl;
    cout << "THE END" << endl;
  return 0;
}
