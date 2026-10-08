#ifndef DICE_H
#define DICE_H

/* Dice state & UI flags */
enum Choice      { UNDER, OVER, EXACT, NONE };
enum ResultState { IDLE, SHOW_WIN, SHOW_LOSS };

struct Dice {
    /* cup animation */
    float cupWidth, cupHeight;
    float cupPosX, cupVelX, cupRange;

    /* dice values */
    int   die1, die2, total;
    bool  diceRevealed;
    Choice playerChoice;

    /* UI flow flags */
    bool  bettingUIActive;
    bool  choiceUIActive;
    bool  revealUIActive;
    bool  resultUIActive;
    bool  addMode;
    ResultState resultState;

    int colDie1, colDie2;

    Dice() :
        cupWidth(200.0f), 
        cupHeight(200.0f),
        cupPosX(0),
        cupVelX(4.0f),
        cupRange(50.0f),
        die1(0), die2(0), total(0),
        diceRevealed(false), playerChoice(NONE),
        bettingUIActive(false),
        choiceUIActive(false),
        revealUIActive(false),
        resultUIActive(false),
        addMode(true),
        resultState(IDLE)
    {}
};

extern Dice dice;
extern GLuint diceTex[4][6];
extern GLuint DiceCupTex;

#endif /* DICE_H */