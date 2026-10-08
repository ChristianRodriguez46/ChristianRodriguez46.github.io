// Christian Rodriguez
// 10/7/25

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream ifile;
    
    int count = 0, num;
    int number[100];

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input file>\n";
    }

    ifile.open(argv[1]);
    if (ifile.fail()) {
        cerr << argv[1] << " failed to open\n";
    }

    while(ifile >> num) {
        number[count++] = num;
    }

    for(int i = count-1; i>-1; i--) {
        cout << number[i] << endl;
    }

    ifile.close();
    return 0;
}