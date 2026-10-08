#ifndef BOLAYVAR_H
#define BOLAYVAR_H

// menu stuff
extern int  click(int savex, int savey, int& done);
extern int  check_esc(int x);
extern void drawBackground();
//added in take values to void
extern void drawBJBackground(float r, float gg, float b);
extern void drawMenuLogo();
extern void drawMenuOptions(int x);
extern void drawButtonTxt();
extern void beginSlots();
extern void initBensTexture();
extern void t8Intro();
void        beginBJPlay();
void        handleBlackJackGame(int x);
void        bjUIClickListener(int savex, int savey);
int         bjUIHoverListener(int savex, int savey, int mouseposition);
int         checkhover(int savex, int savey, int mouseposition);
//added these two
extern void initFirstHand();
extern void drawBJShoe(int x, int y, int z, float xScale, float yScale,
                                    float r, float gg, float b);
// blackjack stuff
extern void initShoe();
#endif
