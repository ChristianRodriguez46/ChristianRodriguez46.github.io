#ifndef CRODRIGUEZ4_H
#define CRODRIGUEZ4_H

#include "global.h"
#include "image.h"
#include "dice.h"
#include <algorithm>

/*---------------------------------------------------------------------
 * Dice‑module public interface
 * Author: Christian Rodriguez          Last modified: 2025‑04‑21
 *----------------------------------------------------------------------
*/

/*--------------------------------------------------------------
 * Helper to generate RGBA textures (main.cpp style)
 *-------------------------------------------------------------
*/
unsigned char *buildAlphaData(Image *img);
unsigned char *buildGreenAlphaData(Image *img);

/*--------------------------------------------------------------
* Dice-module public interface
*-------------------------------------------------------------*/
/* size/update */
void updateUIForWindowSize(void);

/* texture loading */
void loadCupTexture(void);
void loadDiceTextures(void);
extern void loadChipTextures(void);

/* dice control */
void roll_dice(void);
void reveal_dice(void);
void Start_Dice(void);

/* input */
void handleDiceKeys(KeySym key);
void handleChoiceInput(int mx, int my);
void handleRevealClick(int mx, int my);
void handleResultInput(int mx, int my);

/* betting */
void processBettingInput(int mx, int my, int button);
void finalizeBet(void);
void resetBet(void);

/* rendering */

void render_dice(void);
void drawDiceBackground();
void renderBettingUI(void);
void renderChoiceUI(void);
void renderResultUI(void);
void renderRevealButton(void);
void renderResult(void);

/* widgets */
void draw_button_colored(float x, float y,
                        float w, float h,
                        const char *label,
                        float r, float g, float b);

/* credits */
void show_credits(void);

#endif
