// Phillip Lakes (Koli)
// CS 3350 Software Engineering
// Image class by Gordon Griesel

#ifndef PHIL_FUNCS_H
#define PHIL_FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "time.h"
#include "reel.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>
#include <map>
#include <chrono>

// Attempt to instantiate Surface
struct Surface {
    unsigned int width;
    unsigned int height;
    unsigned char* data;

    ~Surface() {
        delete[] data; // Free allocated memory
    }
};

struct Reel;
extern Reel* reels[3];

//void calculate_framerate();
GLfloat get_rand( GLfloat max );
void quit(int retcode);
int initGL(GLvoid);
int draw(GLvoid);
int resize(int width, int height);

#endif
