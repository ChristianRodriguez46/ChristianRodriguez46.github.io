/*
 * crodriguez4.cpp
 * Author: Christian Rodriguez
 * Last Modified: 2025-04-24 (moved dice vars to dice.h)
*/
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include "include/x11.h"
#include "include/fonts.h"
#include "include/crodriguez4.h"
#include "include/dice.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "include/blackjack.h"


using namespace std;


Dice dice;
/* ---------- new global ---------- */
static GLuint chipTex[4] = {0, 0, 0, 0};
GLuint diceTex[4][6];
GLuint DiceCupTex = 0;

#define die1             (dice.die1)
#define die2             (dice.die2)
#define total            (dice.total)
#define diceRevealed     (dice.diceRevealed)
#define playerChoice     (dice.playerChoice)
#define bettingUIActive  (dice.bettingUIActive)
#define choiceUIActive   (dice.choiceUIActive)
#define revealUIActive   (dice.revealUIActive)
#define resultUIActive   (dice.resultUIActive)
#define addMode          (dice.addMode)
#define resultState      (dice.resultState)
/* ------------------------------------------------------------------ */

extern Global g;
extern X11_wrapper x11;

static inline void push_ortho(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, g.xres, 0, g.yres, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* ===================================================== *
 *  Dice ‑ INFO overlay & button                         *
 * ===================================================== */
bool renderDiceInfo = false;

/* quick helper – draws textured square at (x,y) */
static inline void drawButtonQuad(float x, float y)
{
    float h = g.tex.buttonImage->height / 12.0f;
    float w = g.tex.buttonImage->width / 15.0f;

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(x - w, y + h); /* TL */
    glTexCoord2f(1, 0);
    glVertex2f(x + w, y + h); /* TR */
    glTexCoord2f(1, 1);
    glVertex2f(x + w, y - h); /* BR */
    glTexCoord2f(0, 1);
    glVertex2f(x - w, y - h); /* BL */
    glEnd();

    glDisable(GL_ALPHA_TEST);
}

/* ---- diceInfoButton (draw) ---- */
void diceInfoButton(void)
{
    GLboolean texWas = glIsEnabled(GL_TEXTURE_2D);
    if (!texWas)
        glEnable(GL_TEXTURE_2D);

    glColor4f(.95f, .95f, .95f, .85f);
    glPushMatrix();
    glTranslatef(g.xres - 80,     /*   right  */
                 g.yres - 35, 0); /* ↑ top    */
    drawButtonQuad(0, 0);
    glPopMatrix();

    Rect r = {0, 0, 0, 0, 0};
    glPushMatrix();
    glTranslatef(g.xres - 80, g.yres - 46.5f, 0);
    glScalef(2, 2, 1);
    r.center = 1;
    ggprint8b(&r, 16, 0xffffff, renderDiceInfo ? "BACK" : "INFO");
    glPopMatrix();

    if (!texWas)
        glDisable(GL_TEXTURE_2D);
}

/* ---- diceInfoButtonClick (hit‑test) ---- */
bool diceInfoButtonClick(int mx, int my)
/* receives *window* coords: origin top‑left */
{
    // float w = g.tex.buttonImage->width  / 15.0f;
    // float h = g.tex.buttonImage->height / 12.0f;

    int left  = 1161;
    int right = 1238;
    int top   = 22; /* distance from top edge   */
    int bot   = 44; /* a few px slop            */

    /* no y‑flip here – use raw window coordinates */
    if (mx > left && mx < right && my > top && my < bot) {
        renderDiceInfo = !renderDiceInfo;
        return true;
    }
    return false;
}

/* -------------------------------------------------------- *
 * Dice Info overlay – centred card, relaxed line spacing
 * -------------------------------------------------------- */
void diceInfoOverlay(void)
{
    if (!renderDiceInfo)
        return;

    push_ortho();

    /* ----- centred card geometry ------------------------ */
    const float cardW = g.xres * 0.70f;           /* 70 % of window width  */
    const float cardH = g.yres * 0.50f;           /* 45 % of window height */
    const float lx    = (g.xres - cardW) * 0.5f;  /* left  x */
    const float by    = (g.yres - cardH) * 0.55f; /* bottom y */
    const float rx    = lx + cardW;               /* right  x */
    const float ty    = by + cardH;               /* top    y */

    /* save texture state */
    GLboolean texOn = glIsEnabled(GL_TEXTURE_2D);
    if (texOn)
        glDisable(GL_TEXTURE_2D);

    /* ----- draw translucent card ------------------------ */
    glColor4f(0, 0, 0, .75f);
    glBegin(GL_QUADS);
    glVertex2f(lx, by);
    glVertex2f(rx, by);
    glVertex2f(rx, ty);
    glVertex2f(lx, ty);
    glEnd();

    if (texOn)
        glEnable(GL_TEXTURE_2D); /* font needs it */

    /* ----- text ----------------------------------------- */
    const int fsTitle = 32; /* font sizes: title & body   */
    const int fsBody  = 18;
    const int vGap    = 28; /* vertical gap between lines */

    Rect r;
    r.center = 1;
    r.left   = g.xres / 2;
    r.bot    = ty - 60; /* start a little below top   */

    ggprint16(&r, fsTitle, 0xffffff, "DICE GAME RULES");

    /* move down & switch to slightly smaller font */
    r.bot -= vGap * 0.7f;
    ggprint16(&r, fsBody, 0xffffff,
              "1)  The cup will shake for seven seconds so start praying");

    r.bot -= vGap;
    ggprint16(&r, fsBody, 0xffffff, "2)  Choose  UNDER  OVER  or  EXACT");

    r.bot -= vGap * 0.8f;
    ggprint16(&r, fsBody, 0xffffff, "     - UNDER  : total below 7");
    r.bot -= vGap * 0.8f;
    ggprint16(&r, fsBody, 0xffffff, "     - OVER   : total above 7");
    r.bot -= vGap * 0.8f;
    ggprint16(&r, fsBody, 0xffffff, "     - EXACT  : total equals 7");

    r.bot -= vGap * 1.0f;
    ggprint16(&r, fsBody, 0xffffff, "3)  Wins payout is 2x       ");
}

/*==================*/
/*     helpers      */
/*==================*/
/* Ensure RNG is seeded exactly once */
static inline void seed_rng_once(void)
{
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(nullptr));
        seeded = true;
    }
}

/*=================================*/
/* window-size-dependent metrics   */
/*=================================*/
/* Re‑compute dice cup size whenever window resizes */
void updateUIForWindowSize(void)
{
    dice.cupWidth  = g.xres * 0.25f;
    dice.cupHeight = g.yres * 0.25f;
}

/* ------ texture loading ------ */
/* Load cup.png as RGBA texture into DiceCupTex */
void loadCupTexture(void)
{
    Image cup("images/cup.png");
    if (!cup.data) {
        fprintf(stderr, "[ERROR] cup.png not found\n");
        return;
    }
    const int cw = cup.width;
    const int ch = cup.height;

    unsigned char* rgba = buildGreenAlphaData(&cup);

    glGenTextures(1, &DiceCupTex);
    glBindTexture(GL_TEXTURE_2D, DiceCupTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cw, ch, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, rgba);
    free(rgba);
}

/* ---------- new loader ---------- */
void loadChipTextures(void)
/* chips.png == one horizontal strip: blue, green, yellow, red */
{
    Image strip("images/chipSheet.png"); /* 4 × 1 grid  */
    if (!strip.data) {
        fprintf(stderr, "[ERROR] chips.png not found\n");
        return;
    }
    const int      cols = 4;
    const int      cw   = strip.width / cols;
    const int      ch   = strip.height;
    unsigned char* rgba = buildAlphaData(&strip);

    for (int c = 0; c < cols; ++c) {
        unsigned char* tile = (unsigned char*)malloc(cw * ch * 4);
        for (int y = 0; y < ch; ++y) {
            int src = (y * strip.width + c * cw) * 4;
            memcpy(tile + y * cw * 4, rgba + src, cw * 4);
        }
        glGenTextures(1, &chipTex[c]);
        glBindTexture(GL_TEXTURE_2D, chipTex[c]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cw, ch, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, tile);
        free(tile);
    }
    free(rgba);
}

/* Slice diceSheet.png into 4×6 tiles and upload each to diceTex */
void loadDiceTextures(void)
{
    Image sheet("images/diceSheet.png"); /* 600×900: 4×6 tiles */
    if (!sheet.data) {
        fprintf(stderr, "[ERROR] diceSheet.png not found\n");
        return;
    }
    const int cols = 4;
    const int rows = 6;
    const int cw   = sheet.width / cols;  /* 150 */
    const int ch   = sheet.height / rows; /* 150 */

    unsigned char* rgba = buildAlphaData(&sheet);

    for (int c = 0; c < cols; ++c) {
        for (int r = 0; r < rows; ++r) {
            unsigned char* tile = (unsigned char*)malloc(cw * ch * 4);
            for (int y = 0; y < ch; ++y) {
                int src = ((r * ch + y) * sheet.width + c * cw) * 4;
                memcpy(tile + y * cw * 4, rgba + src, cw * 4);
            }
            glGenTextures(1, &diceTex[c][r]);
            glBindTexture(GL_TEXTURE_2D, diceTex[c][r]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cw, ch, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, tile);
            free(tile);
        }
    }
    free(rgba);
}
/* -------- dice logic -------- */
/* Randomize dice, reset UI state, prompt player for choice */
void roll_dice(void)
{
    seed_rng_once();
    die1         = rand() % 6 + 1;
    die2         = rand() % 6 + 1;
    total        = die1 + die2;
    diceRevealed = false;
    playerChoice = NONE;
    resultState  = IDLE;
    printf("[INFO] Dice rolled - choose UNDER / OVER / EXACT.\n");
}

/* Reveal dice faces, evaluate win/lose, update currency */
void reveal_dice(void)
{
    if (diceRevealed)
        return;

    seed_rng_once();
    dice.colDie1 = rand() % 4;
    dice.colDie2 = rand() % 4;
    /* optional: make sure duplicates look different */
    if (die1 == die2 && dice.colDie2 == dice.colDie1)
        dice.colDie2 = (dice.colDie2 + 1) % 4;

    diceRevealed = true;
    bool win     = (playerChoice == UNDER && total < 7) ||
               (playerChoice == OVER && total > 7) ||
               (playerChoice == EXACT && total == 7);

    resultState    = win ? SHOW_WIN : SHOW_LOSS;
    resultUIActive = true;
    choiceUIActive = false;
    revealUIActive = false;

    if (win) {
        g.currency += g.currentBet * 2;
        g.winstreak++;
    } else {
        g.winstreak = 0;
    }
    g.gameInProgress = false;
    printf("[INFO] %d + %d = %d — %s\n", die1, die2, total,
           win ? "WIN" : "LOSS");
}

/* ------------ cup physics ------------- */
/* Simple side‑to‑side physics for rolling cup */
static void cupPhysics(void)
{
    dice.cupPosX += dice.cupVelX;
    if (dice.cupPosX > dice.cupRange)
        dice.cupVelX = -fabs(dice.cupVelX);
    if (dice.cupPosX < -dice.cupRange)
        dice.cupVelX = fabs(dice.cupVelX);
}

/* ---------------------*/
/*  rendering helpers   */
/* ---------------------*/
void drawDiceBackground()
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, g.tex.dicetex);
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
static void drawCup(float cx, float cy, float w, float h)
{
    GLboolean wasTex = glIsEnabled(GL_TEXTURE_2D);
    if (!wasTex)
        glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);

    glBindTexture(GL_TEXTURE_2D, DiceCupTex);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(cx - w, cy - h);
    glTexCoord2f(1, 0);
    glVertex2f(cx + w, cy - h);
    glTexCoord2f(1, 1);
    glVertex2f(cx + w, cy + h);
    glTexCoord2f(0, 1);
    glVertex2f(cx - w, cy + h);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    if (!wasTex)
        glDisable(GL_TEXTURE_2D);
}

/*----------------------------------------------------------------
 * Draw one circular poker-chip sprite, centred on (cx,cy) with the
 *--------------------------------------------------------------*/
static inline void drawChip(GLuint tex, float cx, float cy, float dia,
                            const char* amount)
{
    float hw = dia * 0.5f; /* half-width / half-height  */

    GLboolean texEn = glIsEnabled(GL_TEXTURE_2D);
    if (!texEn)
        glEnable(GL_TEXTURE_2D);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, tex);

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(cx - hw, cy + hw);
    glTexCoord2f(1, 0);
    glVertex2f(cx + hw, cy + hw);
    glTexCoord2f(1, 1);
    glVertex2f(cx + hw, cy - hw);
    glTexCoord2f(0, 1);
    glVertex2f(cx - hw, cy - hw);
    glEnd();

    glDisable(GL_ALPHA_TEST);
    if (!texEn)
        glDisable(GL_TEXTURE_2D);

    /* big amount text */
    Rect r;
    r.center = 1;
    r.left   = cx;
    r.bot    = cy - dia * 0.18f; /* vertical centring tweak */
    ggprint16(&r, 48, 0xffffff, "%s", amount);
}

void render_dice(void)
{
    push_ortho();
    glClear(GL_COLOR_BUFFER_BIT);
    drawDiceBackground();

    float cx = g.xres * 0.5f + dice.cupPosX;
    float cy = g.yres * 0.3f;
    float hw = dice.cupWidth * 0.5f;
    float hh = dice.cupHeight * 0.5f;

    drawCup(cx, cy, hw, hh); /* replaces inline quad */
    glFlush();
}

/* 7-second rolling animation, then prompt for choice */
void Start_Dice(void)
{
    dice.cupVelX = 4.0f;
    time_t start = time(nullptr);

    while (difftime(time(nullptr), start) < 7.0) {
        cupPhysics();
        render_dice();
        x11.swapBuffers();
        usleep(30'000);
    }
    dice.cupPosX = dice.cupVelX = 0.0f;
    roll_dice();
    choiceUIActive = true;
}
/* --------------------------------------------
 * Dice‑specific keyboard handler
 *----------------------------------------------*/
void handleDiceKeys(KeySym key)
{
    if (bettingUIActive) { /* betting overlay */
        if (key == XK_KP_Enter || key == XK_space)
            finalizeBet();
        if (key == XK_r)
            resetBet();
        return;
    }

    if (choiceUIActive) { /* choose O/U/E */
        if (key == XK_u)
            playerChoice = UNDER;
        else if (key == XK_o)
            playerChoice = OVER;
        else if (key == XK_e)
            playerChoice = EXACT;
    } else if (revealUIActive && key == XK_r && playerChoice != NONE) {
        reveal_dice();
    }
}
/*======================*/
/*      GUI widgets     */
/*======================*/
void draw_button_colored(float x, float y, float w, float h, const char* label,
                         float r, float g, float b)
{
    GLboolean wasTex = glIsEnabled(GL_TEXTURE_2D);
    if (wasTex)
        glDisable(GL_TEXTURE_2D);

    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y - h);
    glVertex2f(x, y - h);
    glEnd();

    if (wasTex)
        glEnable(GL_TEXTURE_2D);

    Rect rc;
    rc.center = 1;
    rc.left   = x + w / 2;
    rc.bot    = y - h / 2 - 4;
    ggprint16(&rc, 16, 0, "%s", label);
}
static bool isInsideRect(int px, int py, int rx, int ry, int rw, int rh)
{
    int xMin = min(rx, rx + rw);
    int xMax = max(rx, rx + rw);
    int yMin = min(ry, ry - rh);
    int yMax = max(ry, ry - rh);
    return px >= xMin && px <= xMax && py >= yMin && py <= yMax;
}

/* ---------------- BETTING OVERLAY (textured chips) ---------------- */
void renderBettingUI(void)
{
    push_ortho();
    glClear(GL_COLOR_BUFFER_BIT);
    drawDiceBackground();

    /* ---- geometry ---- */
    const float chipDia = g.yres * 0.12f;  /* circle diameter      */
    const float chipGap = chipDia * 0.30f; /* space between chips  */
    const float chipY   = g.yres / 6.0f;
    const float firstX  = g.xres * 0.48f -
                         (1.5f * chipDia) /* centres @ −1.5,-.5,.5,1.5 */
                         - (1.5f * chipGap);

    /* ---- toggle (+/-) & BET! buttons reuse old rectangles ---------- */
    const int bw = 100, bh = 40, spacing = 20;
    const int startX = (g.xres - (bw * 6 + spacing * 5)) / 2;
    const int topY   = g.yres / 6;

    draw_button_colored(startX, topY, bw, bh, addMode ? "+" : "-",
                        addMode ? 0.0f : 1.0f, addMode ? 0.6f : 0.2f, 1.0f);
    draw_button_colored(startX + 5.25 * (bw + spacing), topY, bw, bh, "BET!",
                        0.1f, 0.8f, 0.1f);

    /* ---- draw four chips ------------------------------------------ */
    static const char* chipTxt[4] = {"5", "10", "25", "100"};
    for (int i = 0; i < 4; ++i) {
        float cx = firstX + i * (chipDia + chipGap) + chipDia * 0.5f;

        /* textured disc */
        drawChip(chipTex[i], cx, chipY, chipDia, chipTxt[i]);
    }

    /* ---------- status ribbon ---------- */
    char info[128];
    snprintf(info, sizeof(info), "Balance $%d    Current Bet $%d    Streak %d",
             g.currency, g.currentBet, g.winstreak);

    Rect t;
    t.center = 1;
    t.left   = g.xres / 2;
    t.bot    = g.yres * 0.07f;
    ggprint16(&t, 24, 0xffffffff, "%s", info);

    /* small top‑right button + overlay */
    diceInfoButton();
    diceInfoOverlay();
}
/*  Choice UI    */
void renderChoiceUI(void)
{
    int y = g.yres / 6;
    draw_button_colored(g.xres / 2 - 160, y, 100, 40, "UNDER", .4f, .5f, 1);
    draw_button_colored(g.xres / 2 - 50, y, 100, 40, "EXACT", 1, .5f, 0);
    draw_button_colored(g.xres / 2 + 60, y, 100, 40, "OVER", .5f, 1, .5f);
    /* small top‑right button + overlay */
    diceInfoButton();
    diceInfoOverlay();
}
/*  Result UI    */
void renderResultUI(void)
{
    push_ortho();
    glClear(GL_COLOR_BUFFER_BIT);
    drawDiceBackground();

    /* dice faces */
    float dw = g.xres * 0.10f;
    float dh = dw;
    float cx = g.xres * 0.5f;
    float cy = g.yres * 0.55f;

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);

    /* left die */
    glBindTexture(GL_TEXTURE_2D, diceTex[dice.colDie1][die1 - 1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(cx - dw - 10, cy + dh / 2);
    glTexCoord2f(1, 0);
    glVertex2f(cx - 10, cy + dh / 2);
    glTexCoord2f(1, 1);
    glVertex2f(cx - 10, cy - dh / 2);
    glTexCoord2f(0, 1);
    glVertex2f(cx - dw - 10, cy - dh / 2);
    glEnd();

    /* right die */
    glBindTexture(GL_TEXTURE_2D, diceTex[dice.colDie2][die2 - 1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(cx + 10, cy + dh / 2);
    glTexCoord2f(1, 0);
    glVertex2f(cx + dw + 10, cy + dh / 2);
    glTexCoord2f(1, 1);
    glVertex2f(cx + dw + 10, cy - dh / 2);
    glTexCoord2f(0, 1);
    glVertex2f(cx + 10, cy - dh / 2);
    glEnd();
    glDisable(GL_ALPHA_TEST);

    /* result text */
    renderResult();

    /* action buttons */
    float bw = g.xres * 0.18f;
    float bh = g.yres * 0.08f;
    float y  = g.yres * 0.25f;
    draw_button_colored(cx - (bw - 20), y, bw, bh, "NEW BET", 0.2f, 0.6f, 1);
    draw_button_colored(cx + 20, y, bw, bh, "SAME BET", 0.1f, 0.8f, 0.1f);
    diceInfoButton();
    diceInfoOverlay();
}

void renderRevealButton(void)
{
    draw_button_colored(g.xres / 2 - 50, g.yres / 6 - 60, 100, 40, "REVEAL",
                        .8f, .1f, .1f);
}

void renderResult(void)
{
    const char* msg = (resultState == SHOW_WIN) ? "YOU WON!" : "YOU LOST";
    int         col = (resultState == SHOW_WIN) ? 0x00ff00ff : 0xff0000ff;
    Rect        r   = {g.xres / 2, g.yres / 2, 0, 0, 0};
    r.center        = 1;
    ggprint16(&r, 32, col, "%s", msg);
}
/*  Mouse / click handlers    */
void handleResultInput(int mx, int my)
{

    if (diceInfoButtonClick(mx, my))
        return;

    my       = g.yres - my;
    float bw = g.xres * 0.18f;
    float bh = g.yres * 0.08f;
    float cx = g.xres * 0.5f;
    float y  = g.yres * 0.25f;

    /* NEW BET */
    if (isInsideRect(mx, my, int(cx - bw - 20), int(y), int(bw), int(bh))) {
        resultUIActive  = false;
        bettingUIActive = true;
        resultState     = IDLE;
        return;
    }
    /* SAME BET */
    if (isInsideRect(mx, my, int(cx + 20), int(y), int(bw), int(bh))) {
        if (g.currentBet > g.currency) {
            fprintf(stderr, "[ERROR] Not enough currency.\n");
            return;
        }
        resultUIActive = false;
        g.currency -= g.currentBet;
        printf("[INFO] Bet locked at %d - starting dice.\n", g.currentBet);
        Start_Dice();
    }
}

void handleChoiceInput(int mx, int my)
{
    if (diceInfoButtonClick(mx, my))
        return;

    my             = g.yres - my;
    const int bw   = 100;
    const int bh   = 40;
    int       topY = g.yres / 6;

    if (isInsideRect(mx, my, g.xres / 2 - 160, topY, bw, bh))
        playerChoice = UNDER;
    else if (isInsideRect(mx, my, g.xres / 2 - 50, topY, bw, bh))
        playerChoice = EXACT;
    else if (isInsideRect(mx, my, g.xres / 2 + 60, topY, bw, bh))
        playerChoice = OVER;
    else
        return;

    choiceUIActive = false;
    revealUIActive = true;
    diceInfoButton();
    diceInfoOverlay();
}

void handleRevealClick(int mx, int my)
{
    if (diceInfoButtonClick(mx, my))
        return;

    my = g.yres - my;
    if (isInsideRect(mx, my, g.xres / 2 - 50, g.yres / 6 - 60, 100, 40))
        reveal_dice();
}

void processBettingInput(int mx, int my, int /*button*/)
{
    /* FIRST: give raw screen coords to the helper */
    if (diceInfoButtonClick(mx, my))
        return;

    my = g.yres - my; /* y-flip */

    /* ----- rectangle buttons (+/- and BET!) ------------------------ */
    const int bw = 100, bh = 40, spacing = 20;
    const int startX = (g.xres - (bw * 6 + spacing * 5)) / 2;
    const int topY   = g.yres / 6;

    /* toggle */
    if (isInsideRect(mx, my, startX, topY, bw, bh)) {
        addMode = !addMode;
        return;
    }
    /* BET! */
    if (isInsideRect(mx, my, startX + 5.25 * (bw + spacing), topY, bw, bh)) {
        finalizeBet();
        return;
    }

    /* ----- circular chip hit-tests -------------------------------- */
    const float chipDia = g.yres * 0.12f;
    const float chipGap = chipDia * 0.30f;
    const float chipY   = g.yres / 6.0f;
    const float firstX  = g.xres * 0.5f - (1.5f * chipDia) - (1.5f * chipGap);
    static const int chipVal[4] = {5, 10, 25, 100};

    for (int i = 0; i < 4; ++i) {
        float cx = firstX + i * (chipDia + chipGap) + chipDia * 0.5f;
        float dx = mx - cx;
        float dy = my - chipY;
        if (dx * dx + dy * dy <= (chipDia * 0.5f) * (chipDia * 0.5f)) {
            int delta    = addMode ? chipVal[i] : -chipVal[i];
            g.currentBet = clamp(g.currentBet + delta, 0, g.currency);
            return;
        }
    }
}

void finalizeBet(void)
{
    if (g.currentBet <= 0) {
        fprintf(stderr, "[ERROR] Bet must be > 0\n");
        return;
    }
    if (g.currentBet > g.currency) {
        fprintf(stderr, "[ERROR] Not enough currency\n");
        return;
    }
    printf("[INFO] Bet locked at %d - starting dice.\n", g.currentBet);
    g.currency -= g.currentBet;
    bettingUIActive  = false;
    g.gameInProgress = true;
    Start_Dice();
}
void resetBet(void) { g.currentBet = 0; }

/* Black jack Logic for player and dealer*/
extern void drawCard(int num, int suit, float posx, float posy);

/* draw face‑down card (index 0 of sprite) ------------------------------- */
inline void drawCardBack(float x, float y)
{
    drawCard(0, 0, x, y); /* suit arg ignored for index 0 */
}

/* render both hands ----------------------------------------------------- */
void renderHands()
{
    float w       = bj.cardWidth; /* half-width for offset */
    float spacing = 20.0f;        /* gap between cards      */
    float off     = w + spacing;
    /* ── Player ── */
    int   pn      = bj.pTotalCards > 0 ? bj.pTotalCards : 1;
    float totalP  = off * (pn - 1);
    float startPx = g.xres / 2.0f - totalP / 2.0f;
    float py      = g.yres * 0.35f;
    for (int i = 0; i < bj.pTotalCards; ++i)
        drawCard(bj.playerHand[i], bj.playerSuit[i], startPx + off * i, py);
    /* ── Dealer ── */
    int   dn      = bj.dTotalCards > 0 ? bj.dTotalCards : 1;
    float totalD  = off * (dn - 1);
    float startDx = g.xres / 2.0f - totalD / 2.0f;
    float dy      = g.yres * 0.65f;
    /* first card face-up */
    drawCard(bj.dealerHand[0], bj.dealerSuit[0], startDx, dy);
    /* second card back or face */
    if (bj.hideHole)
        drawCardBack(startDx + off, dy);
    else
        drawCard(bj.dealerHand[1], bj.dealerSuit[1], startDx + off, dy);
    /* any extra cards */
    for (int i = 2; i < bj.dTotalCards; ++i)
        drawCard(bj.dealerHand[i], bj.dealerSuit[i], startDx + off * i, dy);
}

/* totals next to hands--------- */
void renderTotals()
{
    char buf[8];
    Rect r;

    // ─── Player total above their hand ────────────────────────────────
    int playerVal = bj.playerHandTotal;
    sprintf(buf, "%d", playerVal);
    {
        // match the Y you used for renderHands()
        float py = g.yres * 0.35f + bj.cardHeight + 10.0f;
        glPushMatrix();
        glTranslatef(g.xres / 2.0f, py, 0);
        r.bot = r.left = 0;
        ggprint07(&r, 16, 0xffffff, buf);
        glPopMatrix();
    }

    // ─── Dealer total below their hand ────────────────────────────────
    int dealerVis = bj.hideHole
                        ? ((bj.dealerHand[0] > 10)   ? 10
                           : (bj.dealerHand[0] == 1) ? 11
                                                     : bj.dealerHand[0])
                        : bj.dealerHandTotal;
    sprintf(buf, "%d", dealerVis);
    {
        float dy = g.yres * 0.65f - bj.cardHeight - 10.0f;
        glPushMatrix();
        glTranslatef(g.xres / 2.0f, dy, 0);
        r.bot = r.left = 0;
        ggprint07(&r, 16, 0xffffff, buf);
        glPopMatrix();
    }
}
/*End of BlackJack logic*/

/*----------------------*/
/* Credits functionality*/
/*----------------------*/
static void show_child_credits_window()
{
    /* Create and display a child window to show credits */
    Display* dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Child: Could not open display.\n");
        return;
    }
    int    screen   = DefaultScreen(dpy);
    Window root     = DefaultRootWindow(dpy);
    int    winWidth = 350, winHeight = 250;
    Window win =
        XCreateSimpleWindow(dpy, root, 100, 100, winWidth, winHeight, 1,
                            BlackPixel(dpy, screen), WhitePixel(dpy, screen));
    XStoreName(dpy, win, "Credits");
    XSelectInput(dpy, win, ExposureMask | KeyPressMask | StructureNotifyMask);
    XMapWindow(dpy, win);
    XFontStruct* font = XLoadQueryFont(dpy, "10x20");
    if (!font) {
        fprintf(stderr, "Failed to load font.\n");
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
        return;
    }
    GC gc = XCreateGC(dpy, win, 0, NULL);
    XSetFont(dpy, gc, font->fid);
    XSetForeground(dpy, gc, BlackPixel(dpy, screen));
    bool done = false;
    while (!done) {
        /* Process events for window exposure and key presses */
        XEvent e;
        XNextEvent(dpy, &e);
        if (e.type == Expose) {
            XDrawString(dpy, win, gc, 20, 50, "Credits:", 8);
            XDrawString(dpy, win, gc, 20, 80, " Christian Rodriguez", 20);
            XDrawString(dpy, win, gc, 20, 110, " Philip lakes", 12);
            XDrawString(dpy, win, gc, 20, 140, " Haonan Chen", 12);
            XDrawString(dpy, win, gc, 20, 170, " Benjamin Olayvar", 17);
        }
        if (e.type == KeyPress || e.type == DestroyNotify)
            done = true;
    }
    XFreeFont(dpy, font);
    XFreeGC(dpy, gc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}
void show_credits()
{
    /* Fork a process to show the credits window */
    pid_t cpid;
    int   status;
    cpid = fork();
    if (cpid == 0) {
        show_child_credits_window();
        exit(0);
    } else if (cpid > 0) {
        wait(&status);
        if (WIFEXITED(status)) {
            int es = WEXITSTATUS(status);
            printf("Child (credits) exited with status %d\n", es);
        } else {
            printf("Child did not exit normally.\n");
        }
    } else {
        perror("fork");
    }
}