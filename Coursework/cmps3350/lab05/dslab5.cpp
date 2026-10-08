// Author: Christian Rodriguez
// Create Date: 2/18/25
// Spring 25

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>    
#include <cstdlib>  

using namespace std;

const int MAX_NAMES = 1000;

// Bubble sort for an array of strings
void bubbleSort(string arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                string temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    ifstream fin;

    // Case 1: WHO_TEST is enabled
    #ifdef WHO_TEST
        cout << "[WHO_TEST] Running 'who' command...\n";
        system("who > file.txt");
        fin.open("file.txt");
        if (!fin.is_open()) {
            cerr << "ERROR - Could not open data.txt" << endl;
            return 1;
        }

    // Case 2: UNIT_TEST is enabled (but WHO_TEST is NOT)
    #elif defined(UNIT_TEST)
        if (argc < 2) {
            cerr << "ERROR - Usage: " << argv[0] << " <test data file>\n";
            return 1;
        }
        fin.open(argv[1]);
        if (!fin.is_open()) {
            cerr << "ERROR - Could not open " << argv[1] << endl;
            return 1;
        }

    // Case 3: Default production mode
    #else
        cout << "[PRODUCTION] Running 'w' command...\n";
        system("PROCPS_USERLEN=15 w -h > file.txt");
        fin.open("file.txt");
        if (!fin.is_open()) {
            cerr << "ERROR - Could not open file.txt" << endl;
            return 1;
        }
    #endif

    string names[MAX_NAMES];
    int nameCount = 0;
    string line;

    // Read each line and extract usernames
    while (getline(fin, line) && nameCount < MAX_NAMES) {
        if (line.empty()) continue;
        size_t pos = line.find_first_of(" \t");
        string username = (pos == string::npos) ? line : line.substr(0, pos);
        names[nameCount++] = username;
    }
    fin.close();

    // Sort usernames
    bubbleSort(names, nameCount);

    // Count logins per user
    string uniqueNames[MAX_NAMES];
    int loginCounts[MAX_NAMES] = {0};
    int uniqueUserCount = 0;

    if (nameCount > 0) {
        uniqueNames[0] = names[0];
        loginCounts[0] = 1;
        uniqueUserCount = 1;

        for (int i = 1; i < nameCount; i++) {
            if (names[i] == uniqueNames[uniqueUserCount - 1]) {
                loginCounts[uniqueUserCount - 1]++;
            } else {
                uniqueNames[uniqueUserCount] = names[i];
                loginCounts[uniqueUserCount] = 1;
                uniqueUserCount++;
            }
        }
    }

    // Determine max login count
    int maxLoginCount = 0;
    for (int i = 0; i < uniqueUserCount; i++) {
        if (loginCounts[i] > maxLoginCount)
            maxLoginCount = loginCounts[i];
    }

    // Frequency array
    int frequency[MAX_NAMES] = {0};
    for (int i = 0; i < uniqueUserCount; i++) {
        frequency[loginCounts[i]]++;
    }

    // Display output
    #ifdef WHO_TEST
        cout << "data.txt Login statistic\n";
    #elif defined(UNIT_TEST)
        cout << "Unit test Login statistic\n";
    #else
        cout << "Odin current Login statistic\n";
    #endif

    time_t T;
    time(&T);
    printf("Current time: %s\n", ctime(&T));

    // Output formatted login data
    for (int i = 1; i <= maxLoginCount; i++) {
        if (frequency[i] > 0) {
            cout << i << " login" << (i > 1 ? "s" : "") << ": ";
                            cout << frequency[i] << " users" << endl;
        }
    }

    return 0;
}
