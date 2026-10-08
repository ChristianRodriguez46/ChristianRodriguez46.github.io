#ifndef HCHEN_H
#define HCHEN_H
#include <ctime>

extern void gameInfo(int xx);
extern void displayInfo();
extern void infoRetangle();
extern bool infoButton(int x, int y);
extern bool disInfo;

extern void intro_physics();
extern void intro_render();
extern int introplay;
extern bool introstart;
extern void intro_text();

extern void playBJ();
extern void check2CardBJ();
extern void hit();
extern int dealerHands();
extern int playerHands();
extern void dealerCheckHand();
extern void dealerPlay();
extern void sortHands();
extern void bjPayout();
extern bool standRender;
extern bool hitRender;
extern bool doubleRender;
extern int payoutType;
extern void drawCardBack(float x, float y);
extern void renderHands();
extern void renderTotals();

extern bool renderBJInfo;
extern void bjButtonRender();
extern void bjButtonClick(int x, int y);
extern void renderDoubleButton();
extern void renderHitButton();
extern void renderStandButton();
extern void bjInfoRender();
extern void bjInfo();
extern void bjInfoButton();
extern time_t start_time;
#endif