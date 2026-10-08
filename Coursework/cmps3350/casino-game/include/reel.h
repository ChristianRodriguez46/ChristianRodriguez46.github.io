#ifndef REEL_H
#define REEL_H

#include <GL/gl.h>
#include <iostream>
#include <cmath>

struct Reel {
    GLfloat speed;
    GLfloat degree;
    bool stopped;
    GLfloat begin;

    void start();
    static void stop();
    static int winner();
    static int num_stopped();
    static bool all_stopped();
    int position();
    bool at_stop_position();
    static int stop_position(Reel *reel);
    void spin();

    Reel();
};

extern Reel* reels[3];

#endif
