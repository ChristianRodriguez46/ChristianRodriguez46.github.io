#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const char fname[] = "/home/fac/gordon/public_html/3350/dictionary.txt";
const char Vowels[5] = {'a','e','i','o','u'};

int countVowels(const char vowels[], const char word[]) {
    int count = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < 5; j++) {
            if (word[i] == vowels[j])
                count++;
        }
    }
    return count;
}
int main() 
{
    ifstream fin;
    fin.open(fname);
    if (fin.fail()) {
        cerr << "Error - opening for input. " << fname << endl;
        exit(0);
    }
    char word[200];
    int totalCount = 0;
    char longestWord[200] = "";
    int WrapCount = 0;
    cout << endl;
    cout << "3350 Lab-10 Challenge number: 3" << endl;
    cout << endl;

    fin >> word;
    while (!fin.eof()) {
        int len = strlen(word);
        int longestLength = strlen(longestWord);
        if (len >= 2) {
            int vowelsCount = countVowels(Vowels, word);
            int nonVowelCount = len - vowelsCount;
            if (nonVowelCount == 1) {
                if (WrapCount + len == 80) {
                    cout << word << endl;
                    WrapCount = 0;
                } else if (WrapCount + (len + 1) > 80) {
                    cout << endl;
                    cout << word << " ";
                    WrapCount = len + 1;
                } else {
                    cout << word << " ";
                    WrapCount += (len + 1);
                }
                totalCount++;
                if (len > longestLength) {
                    strcpy(longestWord, word);
                }
            }
        }
        fin >> word;
    }
    cout << endl;
    cout << "\nTotal number of words with exactly one non-vowel: "; 
    cout << totalCount << endl;
    if (totalCount > 0) {
        cout << "Longest word among these: " << longestWord << endl;
    } else {
        cout << "No qualifying words found." << endl;
    }
    
    fin.close();
    cout << endl;
    return 0;
}

