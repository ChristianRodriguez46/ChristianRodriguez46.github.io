#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const char fname[] = "/home/fac/gordon/public_html/3350/dictionary.txt";
int main() 
{
    ifstream fin;
    fin.open(fname);
    if (fin.fail()) {
        cerr << "Error - opening for input. " << fname << endl;
        exit(0);
    }
    char word[200];
    fin >> word;    //priming read
    while (!fin.eof()) {
        if (strlen(word) <= 4) {
            cout << word << " ";
        }
        // cout << word << " ";
        fin >> word;    //priming read
    }
    fin.close();
    cout << endl;
    return 0;
}