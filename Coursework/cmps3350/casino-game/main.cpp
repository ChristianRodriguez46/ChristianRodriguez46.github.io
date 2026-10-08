//
// program: background.cpp --> main.cpp
// author:  Gordon Griesel
// date:    2017 - 2018
//
// The position of the background QUAD does not change.
// Just the texture coordinates change.
// In this example, only the x coordinates change.
//
#include <GL/glx.h>
#include <GL/glut.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <AL/al.h>
#include "include/blackjack.h"
#include "include/bolayvar.h"
#include "include/button.h"
#include "include/dice.h"
#include "include/crodriguez4.h"
#include "include/fonts.h"
#include "include/global.h"
#include "include/hchen_functions.h"
#include "include/image.h"
#include "include/phil_funcs.h"
#include <iostream>

using namespace std;

// macros
#define MakeVector(x, y, z, v) (v)[0] = (x), (v)[1] = (y), (v)[2] = (z)

/* Aliases so old variable names still compile ------------------ */
extern Dice dice;
#define bettingUIActive  (dice.bettingUIActive)
#define choiceUIActive   (dice.choiceUIActive)
#define revealUIActive   (dice.revealUIActive)
#define resultUIActive   (dice.resultUIActive)
#define resultState      (dice.resultState)

Global g;
bool reelsInitialized = false;
Image img[] = { "images/menu_bg.png",   "images/menu_button.png",
                "images/logo.png",      "images/slot_face.png", 
                "images/blackjacktable.png", "images/chipSheet.png",
                "images/shoe.png", "images/reelFaceSheet.png", 
                "images/cardsSheet.png", "images/cup.png", 
                "images/dicetable.png", "images/t8.png" };
class X11_wrapper {
  private:
    Display*   dpy;
    Window     win;
    GLXContext glc;

  public:
    X11_wrapper()
    {
        GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
        // GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
        setup_screen_res(1280, 720);
        dpy = XOpenDisplay(NULL);
        if (dpy == NULL) {
            printf("\n\tcannot connect to X server\n\n");
            exit(EXIT_FAILURE);
        }
        Window       root = DefaultRootWindow(dpy);
        XVisualInfo* vi   = glXChooseVisual(dpy, 0, att);
        if (vi == NULL) {
            printf("\n\tno appropriate visual found\n\n");
            exit(EXIT_FAILURE);
        }
        Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
        XSetWindowAttributes swa;
        swa.colormap   = cmap;
        swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
                         PointerMotionMask | ButtonPressMask |
                         ButtonReleaseMask | StructureNotifyMask |
                         SubstructureNotifyMask;
        win = XCreateWindow(dpy, root, 0, 0, g.xres, g.yres, 0, vi->depth,
                            InputOutput, vi->visual, CWColormap | CWEventMask,
                            &swa);
        set_title();
        glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
        glXMakeCurrent(dpy, win, glc);
    }
    void cleanupXWindows()
    {
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
    }
    void setup_screen_res(const int w, const int h)
    {
        g.xres = w;
        g.yres = h;
    }
    void reshape_window(int width, int height)
    {
        // window has been resized.
        setup_screen_res(width, height);
        glViewport(0, 0, (GLint)width, (GLint)height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(0, g.xres, 0, g.yres, -1, 1);
        set_title();
    }
    void set_title()
    {
        // Set the window title bar.
        XMapWindow(dpy, win);
        XStoreName(dpy, win, "Ghetto Casino");
    }
    bool   getXPending() { return XPending(dpy); }
    XEvent getXNextEvent()
    {
        XEvent e;
        XNextEvent(dpy, &e);
        return e;
    }
    void swapBuffers() { glXSwapBuffers(dpy, win); }
    void check_resize(XEvent* e)
    {
        // The ConfigureNotify is sent by the
        // server if the window is resized.
        if (e->type != ConfigureNotify)
            return;
        XConfigureEvent xce = e->xconfigure;
        if (xce.width != g.xres || xce.height != g.yres) {
            // Window size did change.
            reshape_window(xce.width, xce.height);
        }
    }
} x11;

void init_opengl(void);
void check_mouse(XEvent* e);
int  check_keys(XEvent* e);
void physics(void);
void render(void);
// global variable
int gameState     = 0;
int mouseposition = 0;
int kill          = 0;
//===========================================================================
//===========================================================================
int main(int argc, char *argv[])
{
    printf("```Welcome to the Ghetto```\n");
    //===================================================
    //glutInit(&argc, argv);
    init_opengl();
    while (gameState != 1) {
        while (x11.getXPending()) {
            XEvent e = x11.getXNextEvent();
            x11.check_resize(&e);
            check_mouse(&e);
            kill = check_keys(&e);
        }
        physics();
        render();
        x11.swapBuffers();
        gameState = kill;
    }
    return 0;
}
unsigned char* buildGreenAlphaData(Image* img)
{
    // Add 4th component to an RGB stream...
    // RGBA
    // When you do this, OpenGL is able to use the A component to determine
    // transparency information.
    // It is used in this application to erase parts of a texture-map from view.
    int            i;
    int            a, b, c;
    unsigned char *newdata, *ptr;
    unsigned char* data = (unsigned char*)img->data;
    newdata             = (unsigned char*)malloc(img->width * img->height * 4);
    ptr                 = newdata;
    for (i = 0; i < img->width * img->height * 3; i += 3) {
        a          = *(data + 0);
        b          = *(data + 1);
        c          = *(data + 2);
        *(ptr + 0) = a;
        *(ptr + 1) = b;
        *(ptr + 2) = c;

        if (abs(a - 24) < 10 && abs(b - 254) < 10 && abs(c - 0) < 10) {
            *(ptr + 3) = 0;   // transparent
        } else {
            *(ptr + 3) = 255; // opaque
        }

        ptr += 4;
        data += 3;
    }
    return newdata;
}
unsigned char* buildGreyAlphaData(Image* img)
{
    // Add 4th component to an RGB stream...
    // RGBA
    // When you do this, OpenGL is able to use the A component to determine
    // transparency information.
    // It is used in this application to erase parts of a texture-map from view.
    int            i;
    int            a, b, c;
    unsigned char *newdata, *ptr;
    unsigned char* data = (unsigned char*)img->data;
    newdata             = (unsigned char*)malloc(img->width * img->height * 4);
    ptr                 = newdata;
    for (i = 0; i < img->width * img->height * 3; i += 3) {
        a          = *(data + 0);
        b          = *(data + 1);
        c          = *(data + 2);
        *(ptr + 0) = a;
        *(ptr + 1) = b;
        *(ptr + 2) = c;

        if (abs(a - 188) < 10 && abs(b - 190) < 10 && abs(c - 192) < 10) {
            *(ptr + 3) = 0;   // transparent
        } else {
            *(ptr + 3) = 255; // opaque
        }

        ptr += 4;
        data += 3;
    }
    return newdata;
}
unsigned char* buildAlphaData(Image* img)
{
    // Add 4th component to an RGB stream...
    // RGBA
    // When you do this, OpenGL is able to use the A component to determine
    // transparency information.
    // It is used in this application to erase parts of a texture-map from view.
    int            i;
    int            a, b, c;
    unsigned char *newdata, *ptr;
    unsigned char* data = (unsigned char*)img->data;
    newdata             = (unsigned char*)malloc(img->width * img->height * 4);
    ptr                 = newdata;
    for (i = 0; i < img->width * img->height * 3; i += 3) {
        a          = *(data + 0);
        b          = *(data + 1);
        c          = *(data + 2);
        *(ptr + 0) = a;
        *(ptr + 1) = b;
        *(ptr + 2) = c;
        //-----------------------------------------------
        // get largest color component...
        //*(ptr+3) = (unsigned char)((
        //		(int)*(ptr+0) +
        //		(int)*(ptr+1) +
        //		(int)*(ptr+2)) / 3);
        // d = a;
        // if (b >= a && b >= c) d = b;
        // if (c >= a && c >= b) d = c;
        //*(ptr+3) = d;
        //-----------------------------------------------
        // this code optimizes the commented code above.
        // code contributed by student: Chris Smith
        // Using bitwise OR makes black (0,0,0) yield 0 in alpha.
        *(ptr + 3) = (a | b | c);
        //-----------------------------------------------
        ptr += 4;
        data += 3;
    }
    return newdata;
}

void init_opengl(void)
{
    glViewport(0, 0, g.xres, g.yres);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, g.xres, 0, g.yres, -1, 1);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    
    // Load the cup texture.
    loadCupTexture();
    // load Dice texture
    loadDiceTextures();
    //load Chip Textures for dice
    loadChipTextures();

    // init the position of the menu buttons and logo
    // buttons spaced out by 87 pixels
    MakeVector(g.xres / 2, 575, 0, menulogo.pos);              // logo
    MakeVector(g.xres / 2, g.yres / 2, 0, dev.pos);            // slots
    MakeVector(g.xres / 2, 430, 0, bslot.pos);                 // slots
    MakeVector(g.xres / 2, 430 - 87, 0, bdice.pos);            // dice
    MakeVector(g.xres / 2, 430 - (87 * 2), 0, bblackjack.pos); // blackjack
    MakeVector(g.xres / 2, 430 - (87 * 3), 0, bexit.pos);      // exit
    //
    g.tex.backImage   = &img[0];
    g.tex.buttonImage = &img[1];
    g.tex.menuLogo    = &img[2];
    g.tex.slotImage   = &img[3];
    g.tex.bjImage     = &img[4];
    g.tex.chipImage   = &img[5];
    g.tex.shoeImage   = &img[6];
    g.tex.reelImage   = &img[7];
    g.tex.cardImage   = &img[8];
    g.tex.cupImage    = &img[9];
    g.tex.diceImage   = &img[10];
    g.tex.t8Image     = &img[11];
    //
    // create menu logo
    glGenTextures(1, &g.tex.menulogotex);
    int w = g.tex.menuLogo->width;
    int h = g.tex.menuLogo->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.menulogotex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char* lgo = buildAlphaData(&img[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 lgo);
    free(lgo);
    //
    // create menu background
    glGenTextures(1, &g.tex.backTexture);
    w = g.tex.backImage->width;
    h = g.tex.backImage->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 g.tex.backImage->data);
    g.tex.xc[0] = 1.0;
    g.tex.yc[1] = 1.0;
    //
    // CupImage /* called from  ->   loadCupTexture(); */
    // glBindTexture(GL_TEXTURE_2D, g.tex.cuptex);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // w = g.tex.cupImage->width;
    // h = g.tex.cupImage->height;
    // unsigned char* cup = buildAlphaData(&img[10]);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
    //                 cup);
    // free(cup);
    //
    // create menu button
    glBindTexture(GL_TEXTURE_2D, g.tex.buttontex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    w = g.tex.buttonImage->width;
    h = g.tex.buttonImage->height;
    unsigned char* but = buildAlphaData(&img[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 but);
    free(but);
    //
    // create shoe
    glGenTextures(1, &g.tex.shoetex);
    w = g.tex.shoeImage->width;
    h = g.tex.shoeImage->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.shoetex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char* shoe = buildAlphaData(&img[6]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 shoe);
    free(shoe);
    //
    // create slot face
    glGenTextures(1, &g.tex.slottex);
    w = g.tex.slotImage->width;
    h = g.tex.slotImage->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.slottex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char* slotface = buildAlphaData(&img[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 slotface);
    //
    // create BJ Table
    glGenTextures(1, &g.tex.bjtex);
    w = g.tex.bjImage->width;
    h = g.tex.bjImage->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.bjtex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 g.tex.bjImage->data);
    g.tex.xc[0] = 1.0;
    g.tex.yc[1] = 1.0;
    //
    // create Dice Table background
    glGenTextures(1, &g.tex.dicetex);
    w = g.tex.diceImage->width;
    h = g.tex.diceImage->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.dicetex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 g.tex.diceImage->data);
    g.tex.xc[0] = 1.0;
    g.tex.yc[1] = 1.0;
    //
    // create menu logo
    glGenTextures(1, &g.tex.chiptex);
    w = g.tex.chipImage->width;
    h = g.tex.chipImage->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.chiptex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char* chip = buildAlphaData(&img[5]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 chip);
    free(chip);
    //
    // create reel
    glGenTextures(1, &g.tex.reeltex);
    w = g.tex.reelImage->width;
    h = g.tex.reelImage->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.reeltex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char* reel = buildAlphaData(&img[7]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 reel);
    free(reel);
    //
    // create cards
    glGenTextures(1, &g.tex.cardtex);
    w = g.tex.cardImage->width;
    h = g.tex.cardImage->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.cardtex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char* card = buildGreyAlphaData(&img[8]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 card);
    free(card);
    //
    // create t8
    glGenTextures(1, &g.tex.t8tex);
    w = g.tex.t8Image->width;
    h = g.tex.t8Image->height;
    glBindTexture(GL_TEXTURE_2D, g.tex.t8tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 g.tex.t8Image->data);
    g.tex.xc[0] = 1.0;
    g.tex.yc[1] = 1.0;
    //
    initialize_fonts();
}

void check_mouse(XEvent* e)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;
	//
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (gameState == 3) {
                        printf("x: %d | y: %d\n",savex,savey);
            if (bettingUIActive) {
                processBettingInput(e->xbutton.x, e->xbutton.y, e->xbutton.button);
                return;
            }
            if (choiceUIActive) {
                handleChoiceInput(e->xbutton.x, e->xbutton.y);
                return;
            }
            if (revealUIActive) {
                handleRevealClick(e->xbutton.x, e->xbutton.y);
                return;
            }
            if (resultUIActive) {
				handleResultInput(e->xbutton.x, e->xbutton.y);
				return;
			}
        }
		if (e->xbutton.button == 1) {
			//Left button is down

            // Use print below to get x and y pos
            printf("x: %d | y: %d\n",savex,savey);

            switch(gameState) {
                case 0:
                if (introplay != 1) {
                disInfo = infoButton(savex, savey);
				gameState = click(savex, savey, kill);
                }
                break;
                case 4:
                bjUIClickListener(savex, savey);
		        bjButtonClick(savex, savey);
                break;
            }
		}
		if (e->xbutton.button==3) {
			//Right button is down
		}
	}
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//Mouse moved
		savex = e->xbutton.x;
		savey = e->xbutton.y;
	}
	
    // checks were the mouse is and returns a position value for hover
    switch (gameState) {
        case 0:
		mouseposition = checkhover(savex,savey,mouseposition); 
        break;
        
        case 4:
        mouseposition = bjUIHoverListener(savex,savey,mouseposition);
        break;
    }
}

int check_keys(XEvent* e)
{
    if (e->type == KeyPress) {
        int key = XLookupKeysym(&e->xkey, 0);

        if (key == XK_Escape) {
            gameState = check_esc(gameState);
        }
        
        ///////temporary add-in by Phil///////////
        if (gameState == 2) {
            if (key == XK_space) {
                for (int i = 0; i < 3; ++i) {
                    reels[i]->start();
                }
            }

            if (key == XK_Tab) {
                
                gameState = 0;
            }
            
        }
        ////////////////////////////////////////////

        if (gameState == 3) {
			handleDiceKeys(key);
		}
        if (key == XK_c) {
            show_credits();
        }
        if (key == XK_m) {
            cout << "gameState = 0\n";
            return gameState = 0;
        }
        if (key == XK_s) {
            cout << "gameState = 2\n";
            return gameState = 2;
        }
        if (key == XK_d) {
			cout << "gameState = 3\n";
			bettingUIActive = true; // Show betting UI first
			return gameState = 3;
		}
        if (key == XK_b) {
            cout << "gameState = 4\n";
            return gameState = 4;
        }
        if (key == XK_Shift_L) {
            // Out like a light, ayy,
            exit(666);
        }
        if (key == XK_space && introplay == 2) {
            introplay  = 0;
            introstart = false;
        }
    }
    return gameState;
}

void physics()
{
    switch (gameState) {
    case 2: // black jack
        break;
    case 4:
    break;
    }
}

void render()
{
    if (introplay == 1) {
        glClear(GL_COLOR_BUFFER_BIT);
        t8Intro();
    } else if (introplay == 2) {
        glClear(GL_COLOR_BUFFER_BIT);
        intro_render();
    } else {
        switch (gameState) {
			case 0:
menu_render:
				glClear(GL_COLOR_BUFFER_BIT);
				drawBackground();
				drawMenuLogo();
				drawMenuOptions(mouseposition);
				drawButtonTxt();
				gameInfo(mouseposition);
                resetBet();
				if (disInfo == true) {
					glClear(GL_COLOR_BUFFER_BIT);
					drawBackground();
					gameInfo(mouseposition);
					displayInfo();
				}
				break;

			case 2:
               if (!reelsInitialized) {
                    cout << "[INFO] Initializing Slot game.\n";
                    for (int x = 0; x < 3; ++x) {
                        reels[x] = new Reel();
                    }
            
                    if (initGL() == 1) {
                        printf("Successfully initialized OpenGL.\n");
                    }
            
                    resize(g.xres, g.yres);
                    reelsInitialized = true;
                }
        
                while (gameState == 2) {
                    while (x11.getXPending()) {
                        XEvent e = x11.getXNextEvent();
                        check_keys(&e);  // Process key events
                    }
            
                    draw();
                    x11.swapBuffers();
            
                    if (gameState != 2) {
                        reelsInitialized = false;
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                        glLoadIdentity();
                        goto menu_render;
                        //render_dice();
                        break;
                    }
                }
				break;

            case 3:
				if (bettingUIActive)
					renderBettingUI();
				else if (choiceUIActive) {
					render_dice();
					renderChoiceUI();
				}
				else if (revealUIActive)
					renderRevealButton();
				else if (resultUIActive)
					renderResultUI();
				else
					render_dice();

				if (resultState != IDLE)
					renderResult();
                break;

			case 4:
            	glClear(GL_COLOR_BUFFER_BIT);
                handleBlackJackGame(mouseposition);
		        bjButtonRender();
		        bjInfoRender();
				break;
        }
    }
}
