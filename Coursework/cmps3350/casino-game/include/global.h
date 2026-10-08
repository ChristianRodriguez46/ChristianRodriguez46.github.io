#ifndef GLOBAL_H
#define GLOBAL_H
#include "image.h"
#include <GL/gl.h>


struct Texture {
    // menu background
    Image* backImage;
    GLuint backTexture;
    // menu logo
    Image* menuLogo;
    GLuint menulogotex;
    float  logo_xc[2];
    float  logo_yc[2];
    // button
    Image* buttonImage;
    GLuint buttontex;
    // Dice Cup
    Image* cupImage;
    GLuint cuptex;
    // Dice Table
    Image* diceImage;
    GLuint dicetex;
    // devmode
    Image* devImage;
    GLuint devtex;
    // slot face
    Image* slotImage;
    GLuint slottex;
    // Black Jack Table
    Image* bjImage;
    GLuint bjtex;
    // Chips
    Image* chipImage;
    GLuint chiptex;
    // Black Jack Shoe
    Image* shoeImage;
    GLuint shoetex;   
    // Cards
    Image* cardImage;
    GLuint cardtex;   
    // reel
    Image* reelImage;
    GLuint reeltex;       
    // t8
    Image* t8Image;
    GLuint t8tex;       
    float  xc[2];
    float  yc[2];
};

class Global {
  public:
    int     xres, yres;
    Texture tex;
    GLuint  silhouetteTexture;
    int     slotpos[3];
    //
    int vsync;
    int winstreak;
    //
    float w;
    float h;
    bool  exec;
    bool  initialSlotPosSet;
    bool  gameInProgress;
    // Betting variables
    int currency;   // Starting currency (chips)
    int currentBet; // Current bet amount

    Global()
    {
        xres              = 1280;
        yres              = 720;
        silhouetteTexture = 0; // Initialized
        //dice
        winstreak = 0;
        vsync = 0;
        //
        exec = true;
        initialSlotPosSet = false;
        gameInProgress    = false;
        currency = 1000;     // Start with 1000 chips
        currentBet = 0;      // Initial bet is 0
    }
};

extern Global g;
#endif // GLOBAL_H
