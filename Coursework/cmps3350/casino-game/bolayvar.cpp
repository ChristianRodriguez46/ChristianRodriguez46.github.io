// Benjamin Olayvar
// last revised: 4/30/2025
//
#include "include/blackjack.h"
#include "include/button.h"
#include "include/fonts.h"
#include "include/global.h"
#include "include/hchen_functions.h"
#include "include/image.h"
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <unistd.h>
#include "include/dice.h"
#include "include/x11.h"


using namespace std;

typedef default_random_engine randomize;
extern Dice dice;
#define bettingUIActive  (dice.bettingUIActive)

Blackjack bj;
//=============BEGIN DRAW MENU STUFF==========================================

void drawBackground()
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(-g.tex.xc[0], g.tex.yc[1]);
    glVertex2i(0, 0);
    glTexCoord2f(-g.tex.xc[0], g.tex.yc[0]);
    glVertex2i(0, g.yres);
    glTexCoord2f(g.tex.xc[1], g.tex.yc[0]);
    glVertex2i(g.xres, g.yres);
    glTexCoord2f(g.tex.xc[1], g.tex.yc[1]);
    glVertex2i(g.xres, 0);
    glEnd();
    glPopMatrix();
}
void drawMenuLogo()
{
    // draw logo for menu
    glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
    glPushMatrix();
    glTranslatef(menulogo.pos[0], menulogo.pos[1], menulogo.pos[2]);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.menulogotex);
    glBegin(GL_QUADS);
    float h = g.tex.menuLogo->height / 2.5;
    float w = g.tex.menuLogo->width / 2.5;
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-w, h); // Top-left
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(w, h); // Top-right
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(w, -h); // Bottom-right
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-w, -h); // Botton-left
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glPopMatrix();
}
void buttonIdleState(int x, int y, int z, int xScale, int yScale, float r,
                     float gg, float b)
{
    glColor4f(r, gg, b, 1.0f);
    glPushMatrix();
    glTranslatef(x, y, z);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);
    glBegin(GL_QUADS);
    float h = g.tex.buttonImage->height / yScale;
    float w = g.tex.buttonImage->width / xScale;
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-w, h); // Top-left
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(w, h); // Top-right
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(w, -h); // Bottom-right
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-w, -h); // Botton-left
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glPopMatrix();
}

void buttonHoverState(int x, int y, int z, int xScale, int yScale)
{
    glColor4f(1.0f, 0.53f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(x, y, z);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);
    glBegin(GL_QUADS);
    float h = g.tex.buttonImage->height / yScale;
    float w = g.tex.buttonImage->width / xScale;
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-w, h); // Top-left
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(w, h); // Top-right
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(w, -h); // Bottom-right
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-w, -h); // Botton-left
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glPopMatrix();
}
void drawButtonTxt()
{
    Rect r[2];
    // slots text
    glPushMatrix();
    glTranslatef(bslot.pos[0], bslot.pos[1] - 30, 0);
    glScalef(5.0f, 5.0f, 1); // scale up 500%
    r[0].bot  = 0;
    r[0].left = 0;
    ggprint8b(&r[0], 16, 0xffffff, "SLOTS");
    glPopMatrix();
    // dice text
    glPushMatrix();
    glTranslatef(bdice.pos[0], bdice.pos[1] - 30, 0);
    glScalef(5.0f, 5.0f, 1); // scale up 500%
    r[1].bot  = 0;
    r[1].left = 0;
    ggprint8b(&r[1], 16, 0xffffff, "DICE");
    glPopMatrix();
    // black jack text
    glPushMatrix();
    glTranslatef(bblackjack.pos[0], bblackjack.pos[1] - 23, 0);
    glScalef(4.0f, 4.0f, 1); // scale up 400%
    r[1].bot  = 0;
    r[1].left = 0;
    ggprint8b(&r[1], 16, 0xffffff, "BLACK JACK");
    glPopMatrix();
    // exit text
    glPushMatrix();
    glTranslatef(bexit.pos[0], bexit.pos[1] - 30, 0);
    glScalef(5.0f, 5.0f, 1); // scale up 500%
    r[1].bot  = 0;
    r[1].left = 0;
    ggprint8b(&r[1], 16, 0xffffff, "EXIT");
    glPopMatrix();
}
void drawMenuOptions(int x)
{
    // slots
    if (x == 1) {
        buttonHoverState(bslot.pos[0], bslot.pos[1], bslot.pos[2], 4, 4);
    } else {
        buttonIdleState(bslot.pos[0], bslot.pos[1], bslot.pos[2], 4, 4, 1, 1,
                        1);
    }
    // dice
    if (x == 2) {
        buttonHoverState(bdice.pos[0], bdice.pos[1], bdice.pos[2], 4, 4);
    } else {
        buttonIdleState(bdice.pos[0], bdice.pos[1], bdice.pos[2], 4, 4, 1, 1,
                        1);
    }
    // blackjack
    if (x == 3) {
        buttonHoverState(bblackjack.pos[0], bblackjack.pos[1],
                         bblackjack.pos[2], 4, 4);
    } else {
        buttonIdleState(bblackjack.pos[0], bblackjack.pos[1],
                        bblackjack.pos[2], 4, 4, 1, 1, 1);
    }
    // exit
    if (x == 4) {
        buttonHoverState(bexit.pos[0], bexit.pos[1], bexit.pos[2], 4, 4);
    } else {
        buttonIdleState(bexit.pos[0], bexit.pos[1], bexit.pos[2], 4, 4, 1, 1,
                        1);
    }
}
int click(int savex, int savey, int& done)
{
    if (savex > 490 && savex < 490 + 300 && savey > 250 && savey < 250 + 75) {
        printf("[STATE] Slot selected.\n");
        return 2;
    } else if (savex > 490 && savex < 490 + 300 && savey > 335 &&
               savey < 335 + 75) {
        bettingUIActive = true;
        printf("[STATE] Dice selected.\n");
        return 3;
    } else if (savex > 490 && savex < 490 + 300 && savey > 425 &&
               savey < 425 + 75) {
        printf("[STATE] Black Jack selected.\n");
        return 4;
    } else if (savex > 490 && savex < 490 + 300 && savey > 512 &&
               savey < 512 + 75) {
        printf("[STATE] Exit selected.\n");
        return 1;
    } else {
        return done = 0;
    }
}
int checkhover(int savex, int savey, int mouseposition)
{
    if (!bj.showUI && !bj.insure) {
        if (savex > 490 && savex < 490 + 300 && savey > 250 &&
            savey < 250 + 75) {
            mouseposition = 1; // Menu Slots
        } else if (savex > 490 && savex < 490 + 300 && savey > 335 &&
                   savey < 335 + 75) {
            mouseposition = 2; // Menu Dice
        } else if (savex > 490 && savex < 490 + 300 && savey > 425 &&
                   savey < 425 + 75) {
            mouseposition = 3; // Menu Black Jack
        } else if (savex > 490 && savex < 490 + 300 && savey > 512 &&
                   savey < 512 + 75) {
            mouseposition = 4;
        } else if (savex > 1162 && savex < 1238 && savey > 672 &&
                   savey < 696) {
            mouseposition = 5;
        } else {
            mouseposition = 0;
        }
    } else if (bj.showUI && bj.insure) {
        if (savex > 490 && savex < 490 + 300 && savey > 512 &&
            savey < 512 + 75) {
            mouseposition = 4;
        } else if (savex > 1162 && savex < 1238 && savey > 672 &&
                   savey < 696) {
            mouseposition = 5;
        } else {
            mouseposition = 0;
        }
    }
    return mouseposition;
}
//====================END DRAW MENU STUFF=====================================
//
//==================BEGIN BLACK JACK STUFF====================================
void bjUIClickListener(int savex, int savey)
{
    if (!bj.allIn && bj.showUI) {
        if (savex > 445 && savex < 531 && savey > 280 && savey < 365) {
            g.currentBet += 5;
            bj.betarray[bj.betarraypointer++] = 5;
        } else if (savex > 445 + (100 * 1) && savex < 531 + (100 * 1) &&
                   savey > 280 && savey < 365) {
            g.currentBet += 10;
            bj.betarray[bj.betarraypointer++] = 10;
        } else if (savex > 445 + (100 * 2) && savex < 531 + (100 * 2) &&
                   savey > 280 && savey < 365) {
            g.currentBet += 25;
            bj.betarray[bj.betarraypointer++] = 25;
        } else if (savex > 445 + (100 * 3) && savex < 531 + (100 * 3) &&
                   savey > 280 && savey < 365) {
            g.currentBet += 100;
            bj.betarray[bj.betarraypointer++] = 100;
        }
    }
    if (bj.showUI && savex > 522 && savex < 758 && savey > 498 &&
        savey < 554) {
        bj.showUI        = false;
        bj.allIn         = false;
        g.gameInProgress = true;
        g.currency -= g.currentBet;

        for (int i = 0; i < bj.betarraypointer + 1; i++) {
            bj.betarray[i] = 0;
        }
        bj.betarraypointer = 0;
    }

    if (bj.showUI && savex > 567 && savex < 713 && savey > 570 &&
        savey < 605) {
        g.currentBet -= bj.betarray[bj.betarraypointer--];
        if (g.currentBet < 0) {
            g.currentBet       = 0;
            bj.betarraypointer = 0;
        }

        if (bj.showUI && g.currentBet < g.currency) {
            bj.allIn = false;
        }
    }

    if (bj.showUI && g.currentBet >= g.currency) {
        g.currentBet = g.currency;
    }
}
int bjUIHoverListener(int savex, int savey, int mouseposition)
{
    if (bj.showUI && !bj.insure) {
        if (savex > 522 && savex < 758 && savey > 498 && savey < 554) {
            mouseposition = 6;
        } else if (bj.showUI && savex > 567 && savex < 713 && savey > 570 &&
                   savey < 605) {
            mouseposition = 7;
        } else {
            mouseposition = 0;
        }
    } else if (bj.showUI && bj.insure) {
        if (savex > 522 && savex < 758 && savey > 498 && savey < 554) {
            mouseposition = 8;
        } else if (savex > 522 && savex < 758 && savey > 560 && savey < 617) {
            mouseposition = 9;
        } else {
            mouseposition = 0;
        }
    }
    return mouseposition;
}
void drawBJBackground(float r, float gg, float b)
{
    glColor3f(r, gg, b);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, g.tex.bjtex);
    glBegin(GL_QUADS);
    glTexCoord2f(-g.tex.xc[0], g.tex.yc[1]);
    glVertex2i(0, 0);
    glTexCoord2f(-g.tex.xc[0], g.tex.yc[0]);
    glVertex2i(0, g.yres);
    glTexCoord2f(g.tex.xc[1], g.tex.yc[0]);
    glVertex2i(g.xres, g.yres);
    glTexCoord2f(g.tex.xc[1], g.tex.yc[1]);
    glVertex2i(g.xres, 0);
    glEnd();
    glPopMatrix();
}
void drawChipsFull(int x, int y, int z, float xScale, float yScale)
{
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(x, y, z);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.chiptex);
    glBegin(GL_QUADS);
    float h = g.tex.chipImage->height / yScale;
    float w = g.tex.chipImage->width / xScale;
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-w, h); // Top-left
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(w, h); // Top-right
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(w, -h); // Bottom-right
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-w, -h); // Botton-left
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glPopMatrix();
}
void drawCard(int num, int suit, float posx, float posy)
{
    float w  = bj.cardWidth;
    float h  = bj.cardHeight;
    int   ix = num % 14, iy = suit;
    float tx = (float)ix / 14.0f;
    float ty = (float)iy / 4.0f;

    glPushMatrix();
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.cardtex);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    glTexCoord2f(tx, ty + 0.25f);
    glVertex2f(posx - w, posy - h);
    glTexCoord2f(tx, ty);
    glVertex2f(posx - w, posy + h);
    glTexCoord2f(tx + 0.0714f, ty);
    glVertex2f(posx + w, posy + h);
    glTexCoord2f(tx + 0.0714f, ty + 0.25f);
    glVertex2f(posx + w, posy - h);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glPopMatrix();
}
void drawChipText()
{
    Rect r[2];
    // place your bet
    glPushMatrix();
    glTranslatef(g.xres / 2, g.yres / 1.47, 0);
    glScalef(4.0f, 4.0f, 1); // scale up 500%
    r[0].bot  = 0;
    r[0].left = 0;
    ggprint8b(&r[0], 16, 0xffffff, "place your bet");
    glPopMatrix();
    // 100
    glPushMatrix();
    glTranslatef(g.xres / 1.62, g.yres / 1.79 - 30, 0);
    glScalef(3.5f, 3.5f, 1); // scale up 500%
    r[0].bot  = 0;
    r[0].left = 0;
    ggprint8b(&r[0], 16, 0xffffff, "100");
    glPopMatrix();
    // 25
    glPushMatrix();
    glTranslatef((g.xres / 1.613) - 100, g.yres / 1.79 - 30, 0);
    glScalef(3.5f, 3.5f, 1); // scale up 500%
    r[0].bot  = 0;
    r[0].left = 0;
    ggprint8b(&r[0], 16, 0xffffff, "25");
    glPopMatrix();
    // 10
    glPushMatrix();
    glTranslatef((g.xres / 1.613) - 204, g.yres / 1.79 - 30, 0);
    glScalef(3.5f, 3.5f, 1); // scale up 500%
    r[0].bot  = 0;
    r[0].left = 0;
    ggprint8b(&r[0], 16, 0xffffff, "10");
    glPopMatrix();
    // 5
    glPushMatrix();
    glTranslatef((g.xres / 1.613) - 304, g.yres / 1.79 - 30, 0);
    glScalef(3.5f, 3.5f, 1); // scale up 500%
    r[0].bot  = 0;
    r[0].left = 0;
    ggprint8b(&r[0], 16, 0xffffff, "5");
    glPopMatrix();
}
void drawUIText()
{
    Rect r[2];
    char betStr[64];
    if (bj.showUI && !bj.insure) {
        // current Bet
        if (g.currentBet < g.currency) {
            glPushMatrix();
            glTranslatef(g.xres / 2, g.yres / 2.745, 0);
            glScalef(3.5f, 3.5f, 1); // scale up 500%
            r[0].bot  = 0;
            r[0].left = 0;
            sprintf(betStr, "%d", g.currentBet);
            ggprint8b(&r[0], 16, 0xffffff, betStr);
            glPopMatrix();
        } else {
            glPushMatrix();
            glTranslatef(g.xres / 2, g.yres / 2.745, 0);
            glScalef(3.5f, 3.5f, 1); // scale up 500%
            r[0].bot  = 0;
            r[0].left = 0;
            ggprint8b(&r[0], 16, 0xffffff, "ALL IN");
            glPopMatrix();
            bj.allIn = true;
        }
        // min bet max info
        glPushMatrix();
        glTranslatef(g.xres / 2, g.yres / 3.1, 0);
        glScalef(1.5f, 1.5f, 1); // scale up 500%
        r[0].bot  = 0;
        r[0].left = 0;
        sprintf(betStr, "Minimum Bet: 5 | Maxiumum Bet: %d", g.currency);
        ggprint8b(&r[0], 16, 0xffffff, betStr);
        glPopMatrix();
        // CUrrent balance
        glPushMatrix();
        glTranslatef(g.xres / 10.53, g.yres / 720, 0);
        glScalef(5.0f, 5.0f, 1); // scale up 500%
        r[0].bot  = 0;
        r[0].left = 0;
        sprintf(betStr, "%d", g.currency);
        ggprint8b(&r[0], 16, 0xffffff, betStr);
        glPopMatrix();
        // wallet text
        glPushMatrix();
        glTranslatef(g.xres / 10.53, g.yres / 12.53, 0);
        glScalef(4.0f, 4.0f, 1); // scale up 500%
        r[0].bot  = 0;
        r[0].left = 0;
        ggprint8b(&r[0], 16, 0xffffff, "wallet");
        glPopMatrix();

        // play button
        if (g.currentBet >= 5) {
            glPushMatrix();
            glTranslatef(g.xres / 2, g.yres / 4.45, 0);
            glScalef(5.0f, 5.0f, 1); // scale up 500%
            r[0].bot  = 0;
            r[0].left = 0;
            ggprint8b(&r[0], 16, 0xffffff, "PLAY");
            glPopMatrix();
        } else {
            glPushMatrix();
            glTranslatef(g.xres / 2, g.yres / 4.45, 0);
            glScalef(5.0f, 5.0f, 1); // scale up 500%
            r[0].bot  = 0;
            r[0].left = 0;
            ggprint8b(&r[0], 16, 0xc8c8c8, "PLAY");
            glPopMatrix();
        }
        // buttonIdleState(g.xres/2, g.yres/5.5, 0, 8.5, 8.5, 0.7, 0, 0);
        if (g.currentBet >= 5) {
            glPushMatrix();
            glTranslatef(g.xres / 2, g.yres / 6.35, 0);
            glScalef(3.0f, 3.0f, 1); // scale up 500%
            r[0].bot  = 0;
            r[0].left = 0;
            ggprint8b(&r[0], 16, 0xffffff, "undo");
            glPopMatrix();
        }
    } else if (bj.insure) {
        glPushMatrix();
        glTranslatef(g.xres / 2, g.yres / 2, 0);
        glScalef(4.0f, 4.0f, 1); // scale up 500%
        r[0].bot  = 0;
        r[0].left = 0;
        ggprint8b(&r[0], 16, 0xffffff, "Insurance?");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(g.xres / 2, g.yres / 3.1, 0);
        glScalef(1.5f, 1.5f, 1); // scale up 500%
        r[0].bot  = 0;
        r[0].left = 0;
        ggprint8b(&r[0], 16, 0xffffff, "Are you sure?");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(g.xres / 2, g.yres / 4.45, 0);
        glScalef(5.0f, 5.0f, 1); // scale up 500%
        r[0].bot  = 0;
        r[0].left = 0;
        ggprint8b(&r[0], 16, 0xc8c8c8, "YES");
        glPopMatrix();
        // no insurance please
        glPushMatrix();
        glTranslatef(g.xres / 2, g.yres / 7.3, 0);
        glScalef(5.0f, 5.0f, 1); // scale up 500%
        r[0].bot  = 0;
        r[0].left = 0;
        ggprint8b(&r[0], 16, 0xffffff, "NO");
        glPopMatrix();
        // show current bet
        glPushMatrix();
        glTranslatef(g.xres / 2, g.yres / 2.745, 0);
        glScalef(3.5f, 3.5f, 1); // scale up 500%
        r[0].bot  = 0;
        r[0].left = 0;
        sprintf(betStr, "%d", g.currentBet);
        ggprint8b(&r[0], 16, 0xffffff, betStr);
        glPopMatrix();
        // CUrrent balance
        glPushMatrix();
        glTranslatef(g.xres / 10.53, g.yres / 720, 0);
        glScalef(5.0f, 5.0f, 1); // scale up 500%
        r[0].bot  = 0;
        r[0].left = 0;
        sprintf(betStr, "%d", g.currency);
        ggprint8b(&r[0], 16, 0xffffff, betStr);
        glPopMatrix();
        // wallet text
        glPushMatrix();
        glTranslatef(g.xres / 10.53, g.yres / 12.53, 0);
        glScalef(4.0f, 4.0f, 1); // scale up 500%
        r[0].bot  = 0;
        r[0].left = 0;
        ggprint8b(&r[0], 16, 0xffffff, "wallet");
        glPopMatrix();
    }
}
void drawBJShoe(int x, int y, int z, float xScale, float yScale, float r,
                float gg, float b)
{
    glColor4f(r, gg, b, 1.0f);
    glPushMatrix();
    glTranslatef(x, y, z);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, g.tex.shoetex);
    glBegin(GL_QUADS);
    float h = g.tex.shoeImage->height / yScale;
    float w = g.tex.shoeImage->width / xScale;
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-w, h); // Top-left
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(w, h); // Top-right
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(w, -h); // Bottom-right
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-w, -h); // Botton-left
    glEnd();
    glDisable(GL_BLEND);
    glPopMatrix();
}
void dimBackground()
{
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    float x      = 0;
    float y      = 0;
    float width  = g.xres;
    float height = g.yres;
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
    // glDisable(GL_BLEND);
}
void initShoe()
{
    if (bj.shuffled)
        return;

    int cardpos = 0;

    // Create 6 decks (6 × 52 = 312 cards)
    for (int deck = 0; deck < 6; ++deck) {
        for (int suit = 0; suit < 4; ++suit) {
            for (int value = 1; value <= 13; ++value) {
                bj.shoe[cardpos].value = value;
                bj.shoe[cardpos].suit  = suit;
                cardpos++;
            }
        }
    }

    // Shuffle the shoe
    shuffle(bj.shoe, bj.shoe + bj.maxCards, default_random_engine(time(NULL)));
    cout << "[BLACKJACK] Shoe initialized and shuffled.\n";

    // Set marker
    bj.marker = rand() % 62 + 218;
    cout << "Marker set at: " << bj.marker << endl;

    bj.shuffled = true;
    bj.showUI   = true;
}
void initFirstHand()
{
    if (!bj.initialhand) {
        bj.discard[0] = bj.shoe[bj.currentPos];
        bj.currentPos++;
    }

    bj.initialhand = true;
    if (bj.playerTurn == false && bj.dealerTurn == false) {
        bj.playerTurn = true;
    }
    // Deal two cards to player and dealer
    if (bj.dealFirstHand == false) {
        for (int i = 0; i < 2; i++) {
            Card pCard       = bj.shoe[bj.currentPos++];
            Card dCard       = bj.shoe[bj.currentPos++];
            bj.playerHand[i] = pCard.value;
            bj.dealerHand[i] = dCard.value;

            // Face cards (J, Q, K) are worth 10
            bj.playerHandTotal += (pCard.value > 10) ? 10 : pCard.value;
            bj.dealerHandTotal += (dCard.value > 10) ? 10 : dCard.value;
        }
        bj.pTotalCards = +2;
        bj.dTotalCards = +2;
        printf("players total cards: %i\n", bj.pTotalCards);
        printf("dealer total cards: %i\n", bj.dTotalCards);

        printf("Dealer: %d \nPlayer: %d, %d\n", bj.dealerHand[0],
               bj.playerHand[0], bj.playerHand[1]);
        bj.dealFirstHand = true;
    }
}

void showUI(int xx)
{
    if (bj.showUI && !bj.insure) {
        drawBJBackground(0.5, 0.5, 0.5);
        drawBJShoe(g.xres / 1.13, g.yres / 1.77, 0, 3, 3, 0.5, 0.5, 0.5);
        drawChipsFull(g.xres / 2, g.yres / 1.82, 0, 5, 5);
        drawChipText();
        buttonIdleState(g.xres / 2, g.yres / 2.53, 0, 4, 6, 0, 0,
                        0); // black bet
        buttonIdleState(g.xres / 10.53, g.yres / 24, 0, 5.5, 5, 0, 0,
                        0); // black wallet

        // play button
        if (g.currentBet >= 5) {
            if (xx == 6) {
                buttonIdleState(g.xres / 2, g.yres / 3.75, 0, 5, 5, 0, 1.0, 0);
            } else {
                buttonIdleState(g.xres / 2, g.yres / 3.75, 0, 5, 5, 0, 0.75,
                                0);
            }
        } else {
            buttonIdleState(g.xres / 2, g.yres / 3.75, 0, 5, 5, 0, 0.5, 0);
        }

        // undo button
        if (g.currentBet >= 5) {
            if (xx == 7) {
                buttonIdleState(g.xres / 2, g.yres / 5.5, 0, 8.5, 8.5, 1.0, 0,
                                0);
            } else {
                buttonIdleState(g.xres / 2, g.yres / 5.5, 0, 8.5, 8.5, 0.75, 0,
                                0);
            }
        }
    } else if (bj.showUI && bj.insure) {
        drawBJBackground(0.5, 0.5, 0.5);
        drawBJShoe(g.xres / 1.13, g.yres / 1.77, 0, 3, 3, 0.5, 0.5, 0.5);
        buttonIdleState(g.xres / 2, g.yres / 2.53, 0, 4, 6, 0, 0,
                        0); // black bet
        buttonIdleState(g.xres / 10.53, g.yres / 24, 0, 5.5, 5, 0, 0,
                        0); // black wallet
        if (xx == 10) {
            buttonIdleState(g.xres / 2, g.yres / 3.75, 0, 5, 5, 0.5, 1.0, 0.0);
        } else {
            buttonIdleState(g.xres / 2, g.yres / 3.75, 0, 5, 5, 1.0, 0.5, 0.0);
        }

        if (xx == 11) {
            buttonIdleState(g.xres / 2, g.yres / 5.5, 0, 5, 5, 0.0, 1.0, 0.0);
        } else {
            buttonIdleState(g.xres / 2, g.yres / 5.5, 0, 5, 5, 0.0, 5.0, 0.0);
        }
    }
    drawUIText();
}
void handleBlackJackGame(int x)
{
    if (!bj.shuffled) {
        initShoe();
    }
    if (bj.showUI) {
        showUI(x);
        // drawCard(12, 0, g.xres / 2, g.yres / 2);
    } else {
        playBJ();
    }
}
void handleBlackJackKeys(int x)
{
    // lock out the player from doing anything until the delt cards or
    // animaiton is complete
    if (bj.delt && !bj.wait) {
        switch (x) {
        case XK_space:
            // bjHit();
            break;

        case XK_d || XK_D:
            // bjDouble();
            break;
        }
    }
}
//====================END BLACK JACK STUFF====================================
//
//====================BEGIN BACKUP SLOT STUFF================================
void t8Intro()
{
    if (introplay == 1) {
        const int   cols        = 4;
        const int   rows        = 18;
        const int   totalFrames = 75;
        const float frameW      = 1.0f / (float)cols;
        const float frameH      = 1.0f / (float)rows;

        const float epsilon = 0.0000f; // to avoid edge bleed

        for (int frame = 0; frame < totalFrames; ++frame) {
            int fx = frame % cols;
            int fy = frame / cols;

            float tx0 = fx * frameW + epsilon;
            float tx1 = (fx + 1) * frameW - epsilon;
            float ty0 = fy * frameH + epsilon;
            float ty1 = (fy + 1) * frameH - epsilon;

            // Setup screen-space orthographic projection

            glClear(GL_COLOR_BUFFER_BIT);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, g.tex.t8tex);

            glColor3f(1.0f, 1.0f, 1.0f);

            glBegin(GL_QUADS);
            glTexCoord2f(tx0, ty1);
            glVertex2i(0, 0);
            glTexCoord2f(tx0, ty0);
            glVertex2i(0, g.yres);
            glTexCoord2f(tx1, ty0);
            glVertex2i(g.xres, g.yres);
            glTexCoord2f(tx1, ty1);
            glVertex2i(g.xres, 0);
            glEnd();

            x11.swapBuffers();
            usleep(1000000 / 24); // 24 FPS
        }
        introplay = 2;
    }
}

void drawSlotFace()
{
    glColor4f(1.0, 1.0, 1.0, 0.9f);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.slottex);
    glBegin(GL_QUADS);
    glTexCoord2f(-g.tex.xc[0], g.tex.yc[1]);
    glVertex2i(0, 0);
    glTexCoord2f(-g.tex.xc[0], g.tex.yc[0]);
    glVertex2i(0, g.yres);
    glTexCoord2f(g.tex.xc[1], g.tex.yc[0]);
    glVertex2i(g.xres, g.yres);
    glTexCoord2f(g.tex.xc[1], g.tex.yc[1]);
    glVertex2i(g.xres, 0);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glPopMatrix();
}
void drawSlotScreens()
{
    // Blue screen
    glColor3f(0.0f, 0.0f, 1.0f);
    float x      = g.xres / 2.0f;
    float y      = g.yres / 5.83f;
    float width  = 345.0f;
    float height = 42.0f;

    float halfW = width / 2.0f;
    float halfH = height / 2.0f;

    glBegin(GL_QUADS);
    glVertex2f(x - halfW, y - halfH); // bottom-left
    glVertex2f(x + halfW, y - halfH); // bottom-right
    glVertex2f(x + halfW, y + halfH); // top-right
    glVertex2f(x - halfW, y + halfH); // top-left
    glEnd();
    glFlush();
    // Red screen
    glColor3f(0.75f, 0.0f, 0.1f);
    x      = g.xres / 2.0f;
    y      = g.yres / 9.06f;
    width  = 345.0f;
    height = 42.0f;

    halfW = width / 2.0f;
    halfH = height / 2.0f;

    glBegin(GL_QUADS);
    glVertex2f(x - halfW, y - halfH); // bottom-left
    glVertex2f(x + halfW, y - halfH); // bottom-right
    glVertex2f(x + halfW, y + halfH); // top-right
    glVertex2f(x - halfW, y + halfH); // top-left
    glEnd();
    glFlush();
    // Red screen 2
    glColor3f(0.75f, 0.0f, 0.1f);
    x      = g.xres / 1.11f;
    y      = g.yres / 2.96f;
    width  = 165.0f;
    height = 58.0f;

    halfW = width / 2.0f;
    halfH = height / 2.0f;

    glBegin(GL_QUADS);
    glVertex2f(x - halfW, y - halfH); // bottom-left
    glVertex2f(x + halfW, y - halfH); // bottom-right
    glVertex2f(x + halfW, y + halfH); // top-right
    glVertex2f(x - halfW, y + halfH); // top-left
    glEnd();
    glFlush();
}
void drawSlotReels()
{
    if (!g.initialSlotPosSet) {
        // init slot reel pos
        srand(time(NULL));
        for (int i = 0; i < 3; i++) {
            g.slotpos[i] = rand() % 9;
        }
        g.initialSlotPosSet = true;
    }

    float h  = 251.0 / 2;
    float w  = h;
    float cx = g.xres / 3.49;
    float cy = g.yres / 1.63;

    float currentPos = g.slotpos[0];
    int   baseIndex  = (int)floor(currentPos);
    float frac       = currentPos - baseIndex;

    // Left Reel
    for (int i = -1; i <= 1; i++) {
        int index = (baseIndex + i + 9) % 9;
        int ix    = index % 3;
        int iy    = index / 3;

        float tx = (float)ix / 3.0;
        float ty = (float)iy / 3.0;

        // vertical offset: each image is 2h tall, and we scroll based on
        // 'frac'
        float yOffset = (i - frac) * (h * 2.0);
        float yPos    = cy - yOffset;

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, g.tex.reeltex);
        glColor4ub(255, 255, 255, 255);
        glBegin(GL_QUADS);
        glTexCoord2f(tx, ty + 0.3333f);
        glVertex2i(cx - w, yPos - h);
        glTexCoord2f(tx, ty);
        glVertex2i(cx - w, yPos + h);
        glTexCoord2f(tx + 0.3333f, ty);
        glVertex2i(cx + w, yPos + h);
        glTexCoord2f(tx + 0.3333f, ty + 0.3333f);
        glVertex2i(cx + w, yPos - h);
        glEnd();
        glPopMatrix();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    //
    // Middle Reel
    cx         = g.xres / 2.002;
    currentPos = g.slotpos[1];
    baseIndex  = (int)floor(currentPos);
    frac       = currentPos - baseIndex;
    for (int i = -1; i <= 1; i++) {
        int index = (baseIndex + i + 9) % 9;
        int ix    = index % 3;
        int iy    = index / 3;

        float tx = (float)ix / 3.0;
        float ty = (float)iy / 3.0;

        // vertical offset: each image is 2h tall, and we scroll based on
        // 'frac'
        float yOffset = (i - frac) * (h * 2.0);
        float yPos    = cy - yOffset;

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, g.tex.reeltex);
        glColor4ub(255, 255, 255, 255);
        glBegin(GL_QUADS);
        glTexCoord2f(tx, ty + 0.3333f);
        glVertex2i(cx - w, yPos - h);
        glTexCoord2f(tx, ty);
        glVertex2i(cx - w, yPos + h);
        glTexCoord2f(tx + 0.3333f, ty);
        glVertex2i(cx + w, yPos + h);
        glTexCoord2f(tx + 0.3333f, ty + 0.3333f);
        glVertex2i(cx + w, yPos - h);
        glEnd();
        glPopMatrix();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    //
    // Right Reel
    cx         = g.xres / 1.405;
    currentPos = g.slotpos[2];
    baseIndex  = (int)floor(currentPos);
    frac       = currentPos - baseIndex;
    for (int i = -1; i <= 1; i++) {
        int index = (baseIndex + i + 9) % 9;
        int ix    = index % 3;
        int iy    = index / 3;

        float tx = (float)ix / 3.0;
        float ty = (float)iy / 3.0;

        // vertical offset: each image is 2h tall, and we scroll based on
        // 'frac'
        float yOffset = (i - frac) * (h * 2.0);
        float yPos    = cy - yOffset;

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, g.tex.reeltex);
        glColor4ub(255, 255, 255, 255);
        glBegin(GL_QUADS);
        glTexCoord2f(tx, ty + 0.3333f);
        glVertex2i(cx - w, yPos - h);
        glTexCoord2f(tx, ty);
        glVertex2i(cx - w, yPos + h);
        glTexCoord2f(tx + 0.3333f, ty);
        glVertex2i(cx + w, yPos + h);
        glTexCoord2f(tx + 0.3333f, ty + 0.3333f);
        glVertex2i(cx + w, yPos - h);
        glEnd();
        glPopMatrix();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}
void beginSlots()
{
    drawSlotReels();
    drawSlotScreens();
    drawSlotFace();
}
//====================END OF BACKUP SLOT STUFF===============================
//
//======================BEGIN MISC STUFF======================================
int check_esc(int x)
{
    // switch case for the esc key
    switch (x) {
    // menu case
    case 0:
        x = 1;
        break;
    // slots case
    case 2:
        x = 0;
        break;
    // dice case
    case 3:
        if (!g.gameInProgress) {
            x = 0;
        }
        break;
    // black jack case
    case 4:
        if (!g.gameInProgress) {
            x           = 0;
            bj.shuffled = false;
        }
        break;
    }
    return x;
}
