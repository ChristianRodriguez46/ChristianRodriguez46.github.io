#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Monster.h"
using namespace std;

//Function Prototypes
int genRandom(int start, int end);
string genName();
string genType();
string genColor();
Monster genMonster();
void displayMonster(Monster m);
void makeMonsterCards(Monster mArr[], int size);

//Main Function
int main(int argc, char* argv[]){
    //Seed the random number generator
    srand (time(NULL));

    //Example of how to Randomly generate a monster
    Monster m1 = genMonster();

    //Print monster info to screen
    displayMonster(m1);

    //Test the makeMonsterCards function
   // Monster test[] = {m1};
   // makeMonsterCards(test, 1);
   
 
    /* TODO 3:
        
        1. Ask the user how many monsters they want and assign it to 'count'
           You can use direct user input or command line arguments

        2. Dynamically create an array of monsters using count provided by user
        Hints:
            -This will require using a pointer and the 'new' operator
            -Review 'Dynamic Memory Allocation' in chapter 9
       
        3. Create a loop that fills array with randomly generated monsters
       
        4. Call makeMonsterCards to generate files for each monster in the array
       
        5. Use the delete command to delete dynamically allocated array right before return 0
    */
    // look at book sample 9-14
    
    int count;
    //ask user how many monsters
    cout << "How many monsters do you want?  ";
    cin >> count;
    //create dynamically create array
    Monster *mArr = new Monster[count];
    //loop fills array with random monster
    for(int i = 0; i < count; i++){
      mArr[i] = genMonster();
    };
    //calls function and uses the array and count
    makeMonsterCards(mArr, count);

    delete [] mArr;
    return 0;
}
//
int genRandom(int start, int end){
    int range = end - start + 1;

    return (rand() % range) + start;
}

string genName(){
    const int SIZE = 100;
    string names[SIZE] = {
        "Damian", "Alexa", "Renee", "Damon", "Jael", "Sheila", "Porter", "Byron", 
        "Malachi", "Madonna", "Odysseus", "Gail", "Celeste", "Joan", "Ahmed", 
        "Daryl", "Dalton", "Uma", "Xavier", "Neville", "Alma", "Hedley", "Marsden", 
        "Kendall", "Vera", "Abdul", "Venus", "Owen", "Harlan", "Stella", "Dominic", 
        "Fuller", "Alyssa", "Rashad", "Aurora", "Vincent", "Macon", "Camden", 
        "Tanisha", "Marvin", "Nola", "Sacha", "Fiona", "Nyssa", "Nelle", "Igor", 
        "Brenden", "Mollie", "Hayden", "Aristotle", "Ulla", "Jakeem", "Leila", 
        "Rahim", "Calvin", "Acton", "Tamekah", "Uma", "Aladdin", "Ivana", "Lunea", 
        "Ishmael", "Alvin", "Alice", "Chester", "Hadassah", "Theodore", "Meghan", 
        "Lysandra", "Edan", "Summer", "Sage", "Germaine", "Stephen", "Sawyer", "Cora", 
        "Denise", "Dara", "Jarrod", "Sara", "Tashya", "Hadassah", "Venus", "Keiko", 
        "Tatyana", "Lucas", "McKenzie", "Jane", "Akeem", "Deacon", "Uriah", "Arthur", 
        "Sean", "Latifah", "Shannon", "Eagan", "Autumn", "August", "Justina", "Dolan"
    };

    return names[genRandom(0,SIZE-1)];
}

string genType(){
    const int SIZE = 25;
    string types[SIZE] = {
        "Wet", "Slimy", "Sticky", "Hot", "Gross", "Dry", "Thick", "Thin", "Skinny", 
        "Rough", "Smooth", "Squishy", "Mushy", "Stringy", "Round", "Furry", "Tiny", 
        "Soft", "Creepy", "Prickly", "Nasty", "Spiky", "Prickly", "Small", "Slippery"
    };

    return types[genRandom(0, SIZE-1)];
}

string genColor(){
    const int SIZE = 120;
    string colors[SIZE] = {
        "Mahogany", "Fuzzy Wuzzy Brown", "Chestnut", "Red Orange", "Sunset Orange", 
        "Bittersweet", "Melon", "Outrageous Orange", "Vivid Tangerine", "Burnt Sienna", 
        "Brown", "Sepia", "Orange", "Burnt Orange", "Copper", "Mango Tango", 
        "Atomic Tangerine", "Beaver", "Antique Brass", "Desert Sand", "Raw Sienna", 
        "Tumbleweed", "Tan", "Peach", "Macaroni and Cheese", "Apricot", "Neon Carrot", 
        "Almond", "Yellow Orange", "Gold", "Shadow", "Banana Mania", "Sunglow", 
        "Goldenrod", "Dandelion", "Yellow", "Green Yellow", "Spring Green", 
        "Olive Green", "Laser Lemon", "Unmellow Yellow", "Canary", "Yellow Green", 
        "Inch Worm", "Asparagus", "Granny Smith Apple", "Electric Lime", "Timberwolf", 
        "Screamin Green", "Fern", "Forest Green", "Sea Green", "Green", "Silver",
        "Mountain Meadow", "Shamrock", "Jungle Green", "Caribbean Green", "Gray",
        "Tropical Rain Forest", "Pine Green", "Robin Egg Blue", "Aquamarine", 
        "Turquoise Blue", "Sky Blue", "Outer Space", "Blue Green", "Pacific Blue", 
        "Cerulean", "Cornflower", "Midnight Blue", "Navy Blue", "Denim", "Blue", 
        "Periwinkle", "Cadet Blue", "Indigo", "Wild Blue Yonder", "Manatee", 
        "Blue Bell", "Blue Violet", "Purple Heart", "Royal Purple", "DooDoo Brown", 
        "Purple Mountains Majesty", "Violet", "Wisteria", "Vivid Violet", 
        "Fuchsia", "Shocking Pink", "Pink Flamingo", "Plum", "Hot Magenta", 
        "Purple Pizzazz", "Razzle Dazzle Rose", "Orchid", "Red Violet", "Eggplant", 
        "Cerise", "Wild Strawberry", "Magenta", "Lavender", "Cotton Candy", 
        "Violet Red", "Carnation Pink", "Razzmatazz", "Piggy Pink", "Jazzberry Jam", 
        "Blush", "Tickle Me Pink", "Pink Sherbet", "Maroon", "Red", "Radical Red", 
        "Mauvelous", "Wild Watermelon", "Scarlet", "Salmon", "Brick Red", "White"
    };

    return colors[genRandom(0, SIZE-1)];
}

Monster genMonster(){
    Monster monster;

    /* TODO 1:
        1. Replace the stubbed litral values with the appropriate gen functions
        Hint: Use genRandom for the eyes, arms, and legs.
    */

    monster.setName(genName());
    monster.setType(genType());
    monster.setColor(genColor());
    monster.setEyes(genRandom(0, 15));
    monster.setArms(genRandom(0,15));
    monster.setLegs(genRandom(0, 15));

    return monster;
}
//look at m.getName() if having error problem

//Displays the information for one monster to the screen
void displayMonster(Monster m){
    cout << "---------------------------" << endl;
    cout << m.getName() << " the Monster" << endl;
    cout << "---------------------------" << endl;
    cout << "TYPE: " << m.getType() << endl;
    cout << "COLOR: " << m.getColor() << endl;
    cout << "NO. OF EYES: " << m.getEyes() << endl;
    cout << "NO. OF ARMS: " << m.getArms() << endl;
    cout << "NO. OF LEGS: " << m.getLegs() << endl;
    cout << "---------------------------" << endl;
}

void makeMonsterCards(Monster mArr[], int size){ 
    
    for(int i = 0; i < size; i++){ 
        ofstream outputFile;
        string fName = "monsters/Monsters_" +mArr[i].getName() + ".txt";
        outputFile.open(fName);

        outputFile << "------------------------" << endl;
        outputFile << mArr[i].getName() << " the Monster\n";
        outputFile << "------------------------" << endl;
        outputFile << "TYPE: " << mArr[i].getType() << endl;
        outputFile << "COLOR: " << mArr[i].getColor() << endl;
        outputFile << "NO. OF EYES: " << mArr[i].getEyes() << endl;
        outputFile << "NO. OF ARMS: " << mArr[i].getArms() << endl;
        outputFile << "NO. of LEGS: " << mArr[i].getLegs() << endl;
        outputFile << "------------------------\n";

        outputFile.close();
     }
}
    /* TODO 2:

        FINISH THIS FUCTION SO THAT IT:
        -Loops through the monster array (from 0 to size) and for each:
            1. Open a file called "monsters/Monster_<name>.txt"
            2. Write the monster information to the file
            3. Close the file genRandom(

        Hints:
            1. Use a for loop and access monster information with mArr[i].attribute
            For example: mArr[i].name

            2. To create the filename you can use string concatenation (The + operator)
    */

