#ifndef BLACKJACK_H
#define BLACKJACK_H

struct Card {
    int value;                /* 0‑13  →  0=back, 1=Ace, 2‑10, 11=J,12=Q,13=K */
    int suit;                 /* 0‑3   →  Clubs, Diamonds, Hearts, Spades      */
};

class Blackjack {
  public:
    /* shoe / hands -------------------------------------------------------- */
    Card shoe[312];
    Card discard[300];
    int  playerHand[5];
    int  dealerHand[5];
    int  playerSuit[5];       /* suit for each card in hand                   */
    int  dealerSuit[5];

    /* meta‑data ----------------------------------------------------------- */
    int  maxCards, currentPos, shoeCardNum, marker;
    int  playerHandTotal, dealerHandTotal;
    int  pTotalCards, dTotalCards;

    /* state flags --------------------------------------------------------- */
    bool shuffled, delt, split, insure, dDown;
    bool initialhand, gameInProgress, wait;
    bool dealerTurn, playerTurn, dealerBust, playerBust;
    bool playerStand, dealerStand, dealFirstHand;
    bool hideHole;            /* true while dealer’s 2nd card is face‑down    */

    /* betting ------------------------------------------------------------- */
    int  betarray[100], betarraypointer;
    // GLuint cards;
    float showUI, allIn;
    float cardWidth, cardHeight;
    float cardPosX, cardPosY, cardVelX;

    /* constructor --------------------------------------------------------- */
    Blackjack()
    {
        cardWidth  = 50.0f;   // was 118
        cardHeight = 80.0f;  // was 180
        maxCards = 312;  marker = 0; currentPos = 0;
        playerHandTotal = dealerHandTotal = 0;
        pTotalCards = dTotalCards = shoeCardNum = betarraypointer = 0;

        shuffled = delt = split = insure = dDown = false;
        initialhand = gameInProgress = wait = false;
        dealerTurn = playerTurn = dealerBust = playerBust = false;
        playerStand = dealerStand = dealFirstHand = false;
        hideHole = true;

        showUI = allIn = 0.0f;
    }
};

extern Blackjack bj;
#endif