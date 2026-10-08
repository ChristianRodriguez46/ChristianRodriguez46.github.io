// Haonan Chen
// May 7, 2025
//
// This file has
// intro animation
// info display
// black jack logic n stuff
#include "include/blackjack.h"
#include "include/bolayvar.h"
#include "include/fonts.h"
#include "include/global.h"
#include "include/hchen_functions.h"
#include "include/image.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

bool disInfo = false;

/*===========================GAME INFO START============================*/

void gameInfo(int xx)
{
    if (xx == 5) {
        glColor4f(1.0f, 0.53f, 0.0f, 1.0f);
        glPushMatrix();
        glTranslatef(1200, 35, 0);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);
        glBegin(GL_QUADS);
        float h = g.tex.buttonImage->height / 12;
        float w = g.tex.buttonImage->width / 15;
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
    } else {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glPushMatrix();
        glTranslatef(1200, 35, 0);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);
        glBegin(GL_QUADS);
        float h = g.tex.buttonImage->height / 12;
        float w = g.tex.buttonImage->width / 15;
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

    Rect r;
    glPushMatrix();
    glTranslatef(1200, 23.5, 0);
    glScalef(2.0f, 2.0f, 1);
    r.bot  = 0;
    r.left = 0;
    if (disInfo == false) {
        // r.left = -32;
        ggprint8b(&r, 16, 0xffffff, "INFO");
    } else if (disInfo == true) {
        // r.left = -15;
        ggprint8b(&r, 16, 0xffffff, "BACK");
    }
    glPopMatrix();
}
bool infoButton(int x, int y)
{
    if (x > 1162 && x < 1238 && y > 672 && y < 696) {
        disInfo = !disInfo;
        gameInfo(5);
    }
    return disInfo;
}
void displayInfo()
{
    infoRetangle();
    Rect r;
    glPushMatrix();
    glTranslatef(100, 520, 0);
    glScalef(3.0f, 3.0f, 1);
    r.bot  = 0;
    r.left = 0;
    ggprint8b(&r, 16, 0xffffff, "Welcome to Ghetto Casino\n");
    ggprint8b(&r, 16, 0xffffff, "Here you can play:");
    ggprint8b(&r, 16, 0xffffff, "SLOTS - DICE - Black Jack");
    ggprint8b(&r, 16, 0xffffff, "Your betting ur lifes savings of 1000$");
    ggprint8b(&r, 16, 0xffffff, "Your Goal is To Earn as much");
    ggprint8b(&r, 16, 0xffffff, "as you can before you lose it all");
    ggprint8b(&r, 16, 0xffffff, "Good Luck and Have Fun Gambling!");
    glPopMatrix();
}
void infoRetangle()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
    float x      = 50.0f;
    float y      = 100.0f;
    float width  = 800.0f;
    float height = 500.0f;
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
    glFlush();
    glDisable(GL_BLEND);
}
/*==========================GAME INFO END==============================*/

float  centerX;
float  centerY;
float  logoPosY     = 0.0f;
float  logoFade     = 0.0f;
float  backFade     = 0.0f;
time_t current_time = 0;
time_t start_time   = 0;
int    introplay    = 1;
bool   introstart   = false;
/*=======================INTRO ANIMATION START=========================*/
void init_background()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1.0f, 1.0f, 1.0f, backFade);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2i(0, g.yres);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2i(g.xres, g.yres);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2i(g.xres, 0);
    glEnd();
    glPopMatrix();

    glDisable(GL_BLEND);
}
void init_intro_logo()
{
    g.tex.logo_xc[0] = 0.0f;
    g.tex.logo_xc[1] = 1.0f;
    g.tex.logo_yc[0] = 0.0f;
    g.tex.logo_yc[1] = 1.0f;
    logoPosY         = g.yres * 0.8f;
}
void intro_logo()
{
    centerX = g.xres / 2.0f;
    centerY = logoPosY;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, logoFade);
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);

    glBindTexture(GL_TEXTURE_2D, g.tex.menulogotex);

    float h = g.tex.menuLogo->height / 2.0f;
    float w = g.tex.menuLogo->width / 2.0f;

    glBegin(GL_QUADS);
    glTexCoord2f(g.tex.logo_xc[0], g.tex.logo_yc[0]);
    glVertex2f(-w, h);
    glTexCoord2f(g.tex.logo_xc[1], g.tex.logo_yc[0]);
    glVertex2f(w, h);
    glTexCoord2f(g.tex.logo_xc[1], g.tex.logo_yc[1]);
    glVertex2f(w, -h);
    glTexCoord2f(g.tex.logo_xc[0], g.tex.logo_yc[1]);
    glVertex2f(-w, -h);
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}
void callMenuButton(int x, int y)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, backFade);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);
    glBegin(GL_QUADS);
    float h = g.tex.buttonImage->height / 4;
    float w = g.tex.buttonImage->width / 4;
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-w, h);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(w, h);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(w, -h);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-w, -h);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glPopMatrix();
    glDisable(GL_BLEND);
}
void callAllMenuButton()
{
    callMenuButton(g.xres / 2, 160);
    callMenuButton(g.xres / 2, 245);
    callMenuButton(g.xres / 2, 330);
    callMenuButton(g.xres / 2, 415);
}
void intro_physics()
{
    float elapsed = time(nullptr) - start_time;
    float offset;

    if (elapsed < 9.0f && elapsed > 1.0f) {
        logoFade += 0.03f;
        offset = sinf(elapsed * 2.0f) * 0.0039f;
        g.tex.logo_yc[0] += offset;
        g.tex.logo_yc[1] += offset;
    }
    if (elapsed > 5.0f) {
        backFade += 0.08f;
    }
}
void intro_render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    if (introplay == 2) {
        if (!introstart) {
            init_intro_logo();
            start_time = time(nullptr);
            introstart = true;
        }

        current_time = time(nullptr);
        if (current_time - start_time < 9.0f) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            intro_logo();
            intro_physics();
            init_background();
            callAllMenuButton();
            intro_text();
        } else {
            introstart = false;
            introplay  = 0;
        }
    }
}
void intro_text()
{
    Rect r;
    glPushMatrix();
    glTranslatef(640, 50, 0);
    glScalef(2.0f, 2.0f, 1);
    r.bot  = 0;
    r.left = 0;
    ggprint8b(&r, 16, 0xffffff, "Press Space to Skip");
    glPopMatrix();
}
/*========================INTRO ANIMATION END==========================*/

int           payoutType = 0;
static time_t pauseStart = 0;
static bool   pausing    = false;
/*=======================BLACKJACK LOGIC START=========================*/
void playBJ()
{
    // set game status

    drawBJBackground(1.0f, 1.0f, 1.0f);
    drawBJShoe(g.xres / 1.13f, g.yres / 1.77f, 0, 3, 3, 1.0f, 1.0f, 1.0f);
    initFirstHand();
    renderHands();
    renderTotals();
    check2CardBJ();
    if (bj.playerStand && !bj.dealerStand && !bj.dealerBust) {
        dealerPlay();
    }
    bool handOver =
        bj.playerBust || bj.dealerBust || (bj.playerStand && bj.dealerStand);

    // static time_t pauseStart = 0;
    // static bool pausing = false;

    if (handOver) {
        if (!pausing) {
            pausing    = true;
            pauseStart = time(nullptr);
            printf("[BJ] Reveal pause start\n");
        } else if (difftime(time(nullptr), pauseStart) >= 3.0) {
            pausing = false;
            printf("[BJ] Hand complete -> payout\n");
            bjPayout();
            for (int i = 0; i < 5; ++i) {
                bj.playerHand[i] = bj.dealerHand[i] = bj.playerSuit[i] =
                    bj.dealerSuit[i]                = 0;
            }
            bj.playerHandTotal = 0;
            bj.dealerHandTotal = 0;
            bj.pTotalCards     = 0;
            bj.dTotalCards     = 0;
            bj.playerBust      = false;
            bj.dealerBust      = false;
            bj.playerStand     = false;
            bj.dealerStand     = false;
            bj.dDown           = false;
            bj.insure          = false;
            bj.initialhand     = false;
            bj.dealFirstHand   = false;
            bj.hideHole        = true;
            bj.showUI          = true;
            g.currentBet       = 0;
            g.gameInProgress   = false;
            bj.gameInProgress  = false;
            standRender        = true;
            hitRender          = true;
            doubleRender       = true;
            payoutType         = 0;
            printf("[BJ] Awaiting new bet\n");
        }
    }
}
void check2CardBJ()
{
    if ((bj.dealerHand[0] >= 10 && bj.dealerHand[1] == 1) ||
        (bj.dealerHand[0] == 1 && bj.dealerHand[1] >= 10)) {
        bj.playerBust = true;
    } else if (((bj.dealerHand[0] >= 10 && bj.dealerHand[1] == 1) ||
                (bj.dealerHand[0] == 1 && bj.dealerHand[1] >= 10)) &&
               ((bj.playerHand[0] >= 10 && bj.playerHand[1] == 1) ||
                (bj.playerHand[0] == 1 && bj.playerHand[1] >= 10))) {
        payoutType = 2;
    } else if ((bj.playerHand[0] >= 10 && bj.playerHand[1] == 1) ||
               (bj.playerHand[0] == 1 && bj.playerHand[1] >= 10)) {
        bj.dealerBust = true;
    }
}
void hit()
{
    /* ------------- PLAYER -------------- */
    if (bj.playerTurn && !bj.playerStand && bj.pTotalCards < 5) {
        Card nc                       = bj.shoe[bj.shoeCardNum++];
        bj.playerHand[bj.pTotalCards] = nc.value;
        bj.playerSuit[bj.pTotalCards] = nc.suit;
        ++bj.pTotalCards;
        bj.playerHandTotal +=
            (nc.value > 10) ? 10 : (nc.value == 1 ? 11 : nc.value);
        printf("--PLAYER TOTAL NOW %d  (cards %d)--\n", bj.playerHandTotal,
               bj.pTotalCards);
        if (bj.playerHandTotal > 21) {
            printf("**RECHECKING PLAYER HAND**");
            bj.playerHandTotal = 0;
            sortHands();
            bj.playerHandTotal = playerHands();
            if (bj.playerHandTotal > 21) {
                printf("--PLAYER BUSTS AFTER ACE ADJUST -> %d--\n",
                       bj.playerHandTotal);
                bj.playerBust = true;
            }
        }
    }
    /*---------------player Turn Ends-------------------*/
}
void dealerPlay()
{
    printf("[BJ] Dealer turn starts at %d\n", bj.dealerHandTotal);
    while (bj.dealerHandTotal <= 16 && bj.dTotalCards < 5) {
        Card nc                       = bj.shoe[bj.shoeCardNum++];
        bj.dealerHand[bj.dTotalCards] = nc.value;
        bj.dealerSuit[bj.dTotalCards] = nc.suit;
        ++bj.dTotalCards;
        bj.dealerHandTotal +=
            (nc.value > 10) ? 10 : (nc.value == 1 ? 11 : nc.value);
        printf("**DEALER TOTAL %d (cards %d)**\n", bj.dealerHandTotal,
               bj.dTotalCards);
        if (bj.dealerHandTotal > 21) {
            bj.dealerHandTotal = 0;
            sortHands();
            bj.dealerHandTotal = dealerHands();
            if (bj.dealerHandTotal > 21) {
                printf("**DEALER BUSTS -> %d**\n", bj.dealerHandTotal);
                bj.dealerBust = true;
                break;
            }
        }
    }
    if (!bj.dealerBust) {
        bj.dealerStand = true;
        printf("[BJ] Dealer stands at %d\n", bj.dealerHandTotal);
    }
    bj.dealerTurn = false;
}
// void dealerHands(int x)
int dealerHands()
{
    int dealerHandValue = 0;
    int aceCount        = 0;
    int bestTotal       = 0;
    for (int i = 0; i < 5; i++) {
        if (bj.dealerHand[i] == 0) {
            continue;
        } else if (bj.dealerHand[i] == 1) {
            aceCount++;
        } else if (bj.dealerHand[i] > 10) {
            dealerHandValue += 10;
        } else {
            dealerHandValue += bj.dealerHand[i];
        }
    }
    bestTotal = dealerHandValue + aceCount;
    if (aceCount > 0 && dealerHandValue + 11 + (aceCount - 1) <= 21) {
        bestTotal = dealerHandValue + 11 + (aceCount - 1);
    }
    printf("**DEALER HAND VALUE AFTER BUST CHECK: %i**\n", bestTotal);
    return bestTotal;
}
int playerHands()
{
    int playerHandValue = 0;
    int aceCount        = 0;
    int bestTotal       = 0;
    for (int i = 0; i < 5; i++) {
        if (bj.playerHand[i] == 0) {
            continue;
        } else if (bj.playerHand[i] == 1) {
            aceCount++;
        } else if (bj.playerHand[i] > 10) {
            playerHandValue += 10;
        } else {
            playerHandValue += bj.playerHand[i];
        }
    }
    bestTotal = playerHandValue + aceCount;
    if (aceCount > 0 && playerHandValue + 11 + (aceCount - 1) <= 21) {
        bestTotal = playerHandValue + 11 + (aceCount - 1);
    }
    printf("--PLAYLER HAND VALUE AFTER BUST CHECK: %i--\n", bestTotal);
    return bestTotal;
}
void sortHands()
{
    int dealersize = sizeof(bj.dealerHand) / sizeof(bj.dealerHand[0]);
    sort(bj.dealerHand, bj.dealerHand + dealersize, greater<int>());
    int playersize = sizeof(bj.playerHand) / sizeof(bj.playerHand[0]);
    sort(bj.playerHand, bj.playerHand + playersize, greater<int>());
}
void dealerCheckHand()
{
    if (bj.dealerHand[0] == 1) {
    }
}
void bjPayout()
{
    // int payoutType = 0;
    if (bj.dDown == true) {
        payoutType = 1;
        printf("Payment type set to double\n");
    }
    switch (payoutType) {
    // normal payout/lose
    case 0:
        if (bj.dealerBust) {
            printf("--YOU WON %i BUCKS--\n", g.currentBet);
            g.currency += g.currentBet * 2;
            printf("--CURRENT CURRENCY: %i--\n", g.currency);
        } else if (bj.playerHandTotal <= 21 &&
                   bj.playerHandTotal > bj.dealerHandTotal) {
            printf("--YOU WON %i BUCKS--\n", g.currentBet);
            g.currency += g.currentBet * 2;
            printf("--CURRENT CURRENCY: %i--\n", g.currency);
        } else if (bj.dealerHandTotal == bj.playerHandTotal) {
            printf("--STANDARD DRAW--\n");
            g.currency += g.currentBet;
        } else {
            printf("--YOU LOST %i BUCKS--\n", g.currentBet);
            // g.currency -= g.currentBet;
            printf("--CURRENT CURRENCY: %i--\n", g.currency);
        }
        break;
    // double down
    case 1:
        if (bj.dealerBust) {
            printf("--YOU WON %i BUCKS--\n", g.currentBet * 2);
            g.currency += g.currentBet * 3;
            printf("--CURRENT CURRENCY: %i--\n", g.currency);
        } else if (bj.playerHandTotal <= 21 &&
                   bj.playerHandTotal > bj.dealerHandTotal) {
            printf("--YOU WON %i BUCKS--\n", g.currentBet * 2);
            g.currency += g.currentBet * 3;
            printf("--CURRENT CURRENCY: %i--\n", g.currency);
        } else if (bj.dealerHandTotal == bj.playerHandTotal) {
            printf("--DOUBLEDOWN DRAW--");
            g.currency += g.currentBet;
        } else {
            printf("--YOU LOST %i BUCKS--\n", g.currentBet);
            g.currency -= g.currentBet;
            printf("--CURRENT CURRENCY: %i--\n", g.currency);
        }
        bj.dDown = false;
        break;
    case 2:
        printf("--DRAW--\n");
        g.currency += g.currentBet;
        printf("--CURRENT CURRENCY: %i--\n", g.currency);
        break;
    }
}
bool hitRender    = true;
bool standRender  = true;
bool doubleRender = true;
void bjButtonRender()
{
    if (!bj.dDown && bj.playerTurn && doubleRender && !bj.showUI) {
        // if (!bj.playerTurn) {
        //     usleep(100000);
        // }
        renderDoubleButton();
    }
    if (bj.playerTurn == true && hitRender == true && !bj.showUI) {
        // if (!bj.playerTurn) {
        //     usleep(100000);
        // }
        renderHitButton();
    }
    if (bj.playerTurn == true && standRender == true && !bj.showUI) {
        // if (!bj.playerTurn) {
        //     usleep(100000);
        // }
        renderStandButton();
    }
    bjInfoButton();
}
void bjButtonClick(int x, int y)
{
    // double down button
    if (x > 1095 && x < 1243 && y > 525 && y < 570) {
        if (bj.playerTurn && !bj.dDown && bj.pTotalCards < 5) {
            printf("--PLAYER CHOSE DOUBLE DOWN--\n");
            bj.dDown = true;
            g.currentBet *= 2;
            printf("--BET IS NOW: %i--\n", g.currentBet * 2);
            hit();
            bj.playerStand = true;
            bj.hideHole    = false;
            printf("--Dealer hole revealed: %d (suit %d)--\n",
                   bj.dealerHand[1], bj.dealerSuit[1]);
        }
    }
    // hit button
    if (x > 1095 && x < 1243 && y > 405 && y < 450) {
        if (bj.playerTurn && !bj.playerStand && !bj.playerBust &&
            bj.pTotalCards < 5) {
            printf("--PLAYER CHOSE HIT--\n");
            hit();
            if (bj.playerBust) {
                bj.playerTurn = false;
            }
        }
    }
    // stand button
    if (x > 1095 && x < 1243 && y > 465 && y < 510) {
        if (bj.playerTurn && !bj.playerStand) {
            printf("--PLAYER CHOSE STAND--\n");
            bj.playerStand = true;
            bj.playerTurn  = false;
            bj.hideHole    = false;
            printf("--Dealer hole revealed: %d (suit %d)--\n",
                   bj.dealerHand[1], bj.dealerSuit[1]);
        }
    }
    // info button
    if (x > 1160 && x < 1240 && y > 670 && y < 695) {
        renderBJInfo = !renderBJInfo;
    }
}
void bjInfoRender()
{
    if (renderBJInfo == true) {
        drawBJBackground(0.5, 0.5, 0.5);
        bjInfo();
        bjInfoButton();
    }
}
/*=======================BLACKJACK LOGIC END===========================*/
bool renderBJInfo = false;
void bjInfo()
{
    Rect r;
    glPushMatrix();
    glTranslatef(640, 625, 0);
    glScalef(2.0f, 2.0f, 1);
    r.bot  = 0;
    r.left = 0;
    ggprint8b(&r, 16, 0xffffff, "RULES:");
    ggprint8b(&r, 16, 0xffffff, "Dealer must hit on 16 or less\n");
    ggprint8b(&r, 16, 0xffffff, " ");
    ggprint8b(&r, 16, 0xffffff, "Hit:");
    ggprint8b(&r, 16, 0xffffff, "Draw another card");
    ggprint8b(&r, 16, 0xffffff, " ");
    ggprint8b(&r, 16, 0xffffff, "Stand:");
    ggprint8b(&r, 16, 0xffffff, "No longer be able to draw cards");
    ggprint8b(&r, 16, 0xffffff, " ");
    ggprint8b(&r, 16, 0xffffff, "Double:");
    ggprint8b(&r, 16, 0xffffff, "Will double your current bet");
    ggprint8b(&r, 16, 0xffffff, "You will only get 1 more card\n");
    ggprint8b(&r, 16, 0xffffff, " ");
    ggprint8b(&r, 16, 0xffffff, "INSURANCE:");
    ggprint8b(&r, 16, 0xffffff, "Offered if dealer first card is ACE");
    ggprint8b(&r, 16, 0xffffff, "If dealer gets 2 card blackjack");
    ggprint8b(&r, 16, 0xffffff, "You will not lose your money");
    ggprint8b(&r, 16, 0xffffff,
              "Or you will get double ur money or something");
    glPopMatrix();
}
void renderDoubleButton()
{
    glColor4f(0.9f, 0.9f, 0.9f, 0.8f);
    glPushMatrix();
    glTranslatef(1170, 170, 0);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);
    glBegin(GL_QUADS);
    float h = g.tex.buttonImage->height / 6;
    float w = g.tex.buttonImage->width / 8;
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

    Rect r;
    glPushMatrix();
    glTranslatef(1170, 160, 0);
    glScalef(2.0f, 2.0f, 1);
    r.bot  = 0;
    r.left = 0;
    ggprint8b(&r, 16, 0xffffff, "DOUBLE");
    glPopMatrix();
}
void renderHitButton()
{
    glColor4f(0.9f, 0.9f, 0.9f, 0.8f);
    glPushMatrix();
    glTranslatef(1170, 290, 0);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);
    glBegin(GL_QUADS);
    float h = g.tex.buttonImage->height / 6;
    float w = g.tex.buttonImage->width / 8;
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

    Rect r;
    glPushMatrix();
    glTranslatef(1170, 280, 0);
    glScalef(2.0f, 2.0f, 1);
    r.bot  = 0;
    r.left = 0;
    ggprint8b(&r, 16, 0xffffff, "HIT");
    glPopMatrix();
}
void renderStandButton()
{
    glColor4f(0.9f, 0.9f, 0.9f, 0.8f);
    glPushMatrix();
    glTranslatef(1170, 230, 0);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);
    glBegin(GL_QUADS);
    float h = g.tex.buttonImage->height / 6;
    float w = g.tex.buttonImage->width / 8;
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

    Rect r;
    glPushMatrix();
    glTranslatef(1170, 220, 0);
    glScalef(2.0f, 2.0f, 1);
    r.bot  = 0;
    r.left = 0;
    ggprint8b(&r, 16, 0xffffff, "STAND");
    glPopMatrix();
}
void bjInfoButton()
{
    glColor4f(0.9f, 0.9f, 0.9f, 0.8f);
    glPushMatrix();
    glTranslatef(1200, 35, 0);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);
    glBegin(GL_QUADS);
    float h = g.tex.buttonImage->height / 12;
    float w = g.tex.buttonImage->width / 15;
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

    Rect r;
    glPushMatrix();
    glTranslatef(1200, 23.5, 0);
    glScalef(2.0f, 2.0f, 1);
    r.bot  = 0;
    r.left = 0;
    if (renderBJInfo == false) {
        ggprint8b(&r, 16, 0xffffff, "INFO");
    } else if (renderBJInfo == true) {
        ggprint8b(&r, 16, 0xffffff, "BACK");
    }
    glPopMatrix();
}