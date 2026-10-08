#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Step
{
    int type;
    int coins;
};

void clear_steps(Step steps[], int size)
{
    //this function sets all the types to be 0 (TILE)
        //and all the coin values to be zero
    for (int i = 0; i < size; i++)
    {
        steps[i].type = 0;
        steps[i].coins = 0;
    }
}

void show_path(Step steps[], int size, int pos)
{
    //this function displays the path on one line
    //each step is displayed as a '-'
    //However, where the player currently is (given by pos)
    //display an 'x'

    for (int i = 0; i < size; i++)
    {
        if (i == pos)
            cout << "X";
        else
            cout << "-";
    }
    cout << endl;
}

void add_coins(Step steps[], int size)
{
    int coin_value[10] = {0, 0, 5, 0, 0, 10, 0, 0, 20, 0};
    //set all the coin values in each of the steps to 
    //a value randomly selected from the coin_values[] array
    //REMEBER: the expression
    // rand() % M
    // will return a value between 0 and M
    for (int i = 0; i < size; i++ )
    {
        steps[i].coins = coin_value[rand() % 10];
    }
}

void set_step_type(Step steps[], int size, const int type, int howmany)
{
    //in howmany locations along the steps array,
    //place howmany of type on the path
    //Example, if howmany is 3 and type is GLUE
    //then you will randomly set 3 of the steps to be of type GLUE
   for (int i=0; i < howmany; i++)
   { 
       int randomType = rand() % size; 
       steps[randomType].type = type;
   }
}

int main()
{
    const int TILE = 0;
    const int OIL = 1;
    const int GLUE = 2;
    const int BANDIT = 3;

    const int DISTANCE = 20;
    Step path[DISTANCE];
    int playerpos = 0;
    bool alive = true;
    char action;
    int coins = 0;

    srand(time(NULL));

    //set all steps in the path to TILE, and all coins to zero
    //TODO - call clear_steps() function
    clear_steps(path, DISTANCE);

    // randomly distribute coins along the path
    // TODO - Call add_coins() function
    add_coins(path, DISTANCE);


    set_step_type(path, DISTANCE, OIL, 3); //sets 3 steps to OIL
    set_step_type(path, DISTANCE, GLUE, 2); //sets 2 steps to GLUE
    set_step_type(path, DISTANCE, BANDIT, 1); //sets 1 step to BANDIT

    //TODO - Set the first step to be TILE
    
    path[0].type = TILE;


    while (alive && playerpos < DISTANCE)
    {
        show_path(path, 20, playerpos);
        cout << "s-step, h-hop > ";
        cin >> action;

        if (path[playerpos].type == OIL && action == 'h')
        {
            cout << "You're in oil. You can only step" << endl;
            action = 's';
        }
        if (path[playerpos].type == GLUE)
        {
            cout << "You stepped in glue. That makes you a glue-ser!" << endl;
            alive = false;
        }


        if (action == 's')
            playerpos++;
        if (action == 'h')
            playerpos += 2;

        // TODO Add the coins found on the current step to
        // player's coins haul
        coins += /* TODO */path[playerpos].coins;

        if (path[playerpos].type == BANDIT )
        {
            cout << "Oh no! A bandit took all your coins!" << endl;
            coins = 0;
        } 
        cout << "COINS: " << coins << endl << endl;
    }
        if (playerpos >= DISTANCE)
        {
            cout << "You WON! You crossed the path unscathed!" << endl;
        } else{
            cout << "You lose. Womp womp." << endl;
        }
    
        return 0;
}
