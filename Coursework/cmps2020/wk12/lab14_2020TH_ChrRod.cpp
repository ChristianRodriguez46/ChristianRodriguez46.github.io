//Christian Rodriguez
#include <iostream>
#include <fstream>
#include <string> // used for .length()

using namespace std;


// Calculate the hash sum for the word as the sum total of each letter’s index value
int calcHash(string word)
{
    int hashSum = 0;         //initalize hash sum to 0
    for (int i = 0; i < word.length(); i++)
    {
        char c = word[i];     //get the current character from the word  
        hashSum += c - 'a' + 1;     //calc the index value of char
    }
    return hashSum % 320;
}

// Read the words from the file, calculate the hash value for each word, and increment the count at collisions[hash_value]
void readWords()    
{
    ifstream fin;
    fin.open("enable1.txt");
    string word;

    int collisions[320] = {0};   //intialize collision array to 0
    while (fin >> word)
    {
        int hashValue = calcHash(word);
        collisions[hashValue]++;
    }
    fin.close();

    //display contents of collision table
    for (int i = 0; i < 320; i++)
    {
        cout << "Collisions at index " << i << ": " << collisions[i] << endl;
    }

    //Find what hash value has the most collisions
    int maxCollisions = 0;
    int maxCollisionsIndex = 0;
    for (int i = 0; i < 320; i++)
    {
        if (collisions[i] > maxCollisions)
        {
            maxCollisions = collisions[i];
            maxCollisionsIndex = i;
        }
    }
    cout << "Hash value that has the most collisions: " << maxCollisionsIndex << endl;
    cout << "Largest number of collisions: " << maxCollisions << endl;
}

int main(){

    readWords();

    return 0;
}
