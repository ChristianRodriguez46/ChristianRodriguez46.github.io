#include <iostream>
#include <string>

using namespace std;

// Function to perform linear search
// Returns the index of the item if found, otherwise returns -1
int find_item_linear(string items[], string item, int size) {
    for (int i = 0; i < size; i++) {
        if (items[i] == item) {
            return i;
        }
    }
    return -1;
}

// Function to perform binary search
// Assumes the array is sorted
// Returns the index of the item if found, otherwise returns -1
int find_item_binary(string items[], string item, int size) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;
        
        if (items[middle] == item) {
            return middle;
        }
        if (items[middle] < item) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}

// Function to sort the array in ascending order
// Uses a bubble sort
void sort(string items[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (items[i] > items[j]) {
                // Swap items[i] and items[j]
                string temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

// Function to find partial matches
// Searches for the pattern within each item in the array
// Stores matching items in the matches array and updates match_count
int find_matches(string items[], string pattern, int size, string matches[]) {
    int match_count = 0;
    for (int i = 0; i < size; i++) {
        
        // .find() searches for the pattern in the current item
        // If the pattern is found, .find() returns the index where it starts
        // If the pattern is not found, .find() returns string::npos
        
        if (items[i].find(pattern) != string::npos) {
            // If the pattern is found, add the current item to matches array
            matches[match_count++] = items[i];
        }
    }
    return match_count;
}

int main() {
    string text[25] = { "winter", "radius", "arthritis", "sponge", "rotation", "brandy", "radium", "crank", "ginger", "ankle", "cooler", "cranium", "potato", "receipt", "keratin", "stool", "termite", "dynamite", "singing", "banker", "thrifty", "longer", "tattoo", "rations", "being"};
    string matches[25];
    int matchCount;

    // Sort the array for binary search
    sort(text, 25);

    int action;
    string input;

    do {
        // Display the menu
        cout << "1- Search for a word using linear" << endl;
        cout << "2- Search for a word using binary" << endl;
        cout << "3- Search for a partial string" << endl;
        cout << "4- Exit" << endl;
        cout << "Action: ";
        cin >> action; 
        cout << endl;

        switch (action) {
            case 1:
                // Perform linear search
                cout << "Enter string: ";
                cin >> input;

                if (find_item_linear(text, input, 25) != -1) {
                    cout << "Found " << input << endl << endl;
                } else {
                    cout << input << " was not found" << endl << endl;
                }
                break;

            case 2:
                // Perform binary search
                cout << "Enter string: ";
                cin >> input;

                if (find_item_binary(text, input, 25) != -1) {
                    cout << "Found " << input << endl << endl;
                } else {
                    cout << input << " was not found" << endl << endl << endl;
                }
                break;

            case 3:
                // Perform partial string search
                cout << "Enter partial search term: ";
                cin >> input;

                matchCount = find_matches(text, input, 25, matches);

                if (matchCount > 0) {
                    cout << "Found ";
                    for (int i = 0; i < matchCount; i++) {
                        cout << matches[i] << " ";
                    }
                    cout << endl << endl;
                } else {
                    cout << "Found no matches" << endl << endl;
                }
                break;
            
            default:
                // Handle invalid action
                // cout << "Invalid action. Please try again." << endl;
                break;
        }
    } while (action != 4); // Continue until the user chooses to exit

    return 0;
}
