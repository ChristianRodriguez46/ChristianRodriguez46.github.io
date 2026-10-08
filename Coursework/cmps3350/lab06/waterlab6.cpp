//
//modified by: Christian Rodriguez
//Last modified: 3/1/25		 Spring 2025
//
//original author: Gordon Griesel
//date:            Fall 2024
//purpose:         OpenGL sample program
//
//This program needs some refactoring.
//We will do this in class together.
//
//
#include <iostream>
using namespace std;
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "fonts.h"


// macro
#define rnd() (float)rand() / (float)RAND_MAX
#define MAX_PARTICLES 400
#define NUM_BOXES 5

//some structures
class Box {
	public:
	int width;
	int height;
	int prev[2];
	float pos[2];
	float vel[2];
	float force[2];
	float color[3];		//Red, green, and blue
	char text[100];
	Box () {
		width = 100;
		height = 50;
		vel[0] = vel[1] = 0.0f;
		color[0] = 0.3f;
		color[1] = 0.7f;
		color[2] = 0.3f;
	}
	// particles
	Box (int w, int h) {
		Box();
		width = w;
		height = h;
	}
} box, particle(4,4);

Box boxes[NUM_BOXES];
Box particles[MAX_PARTICLES];
int n = 0;
void make_particle(int x, int y) {
	if (n >= MAX_PARTICLES)
		return;
	particles[n].width = 3;
	particles[n].height = 3;
	particles[n].pos[0] = x;
	particles[n].pos[1] = y;
	particles[n].vel[0] = rnd() * 2.0f - 1.0;
	particles[n].vel[1] = rnd() * 2.0f - 1.0;
	++n;
}
void delete_particle(int a) {
	if (n == 0)
		return;
	// Optimized
	// particles[a] = particles[n-1];
	// n = n -1;
	particles[a] = particles[--n];
}

class Global {
public:
	int xres, yres;
	Global(){
        xres = 640;
        yres = 480;
       
    };
} g;

class X11_wrapper {
private:
	Display *dpy;
	Window win;
	GLXContext glc;
public:
	~X11_wrapper();
	X11_wrapper();
	void set_title();
	bool getXPending();
	XEvent getXNextEvent();
	void swapBuffers();
	void reshape_window(int width, int height);
	void check_resize(XEvent *e);
	void check_mouse(XEvent *e);
	int check_keys(XEvent *e);
} x11;

//Function prototypes
void init_opengl(void);
void physics(void);
void render(void);
void init_box();

int main()
{
	init_opengl();
	init_box();
	int done = 0;
	//main game loop
	while (!done) {
		//look for external events such as keyboard, mouse.
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.check_resize(&e);
			x11.check_mouse(&e);
			done = x11.check_keys(&e);
		}
		physics();
		render();
		x11.swapBuffers();
		usleep(200);
	}
	return 0;
}

void init_box()
{
    // scale with window size:
    int w = g.xres / 8;   // example: 1/8 of window width
    int h = g.yres / 20;  // example: 1/16 of window height

    // use fractions of the current window size:
    float startX = g.xres * 0.2f; // 20% from the left
    float startY = g.yres * 0.8f; // 80% from the top

    for (int i = 0; i < NUM_BOXES; i++) {
        boxes[i].width  = w;
        boxes[i].height = h;
        // Offset each box to create a stepped layout
        boxes[i].pos[0] = startX + (i * (w * 0.8f));
        boxes[i].pos[1] = startY - (i * (h * 2.5f));

        boxes[i].color[0] = 0.2f;
        boxes[i].color[1] = 0.7f;
        boxes[i].color[2] = 0.3f;

        switch (i) {
            case 0: strcpy(boxes[i].text, "Requirements"); break;
            case 1: strcpy(boxes[i].text, "Design");       break;
            case 2: strcpy(boxes[i].text, "Coding");       break;
            case 3: strcpy(boxes[i].text, "Testing");      break;
            case 4: strcpy(boxes[i].text, "Maintenance");  break;
        }
    }
}



X11_wrapper::~X11_wrapper()
{
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

X11_wrapper::X11_wrapper()
{
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	int w = g.xres, h = g.yres;
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		cout << "\n\tcannot connect to X server\n" << endl;
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		cout << "\n\tno appropriate visual found\n" << endl;
		exit(EXIT_FAILURE);
	} 
	Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	XSetWindowAttributes swa;
	swa.colormap = cmap;
	swa.event_mask =
		ExposureMask | KeyPressMask | KeyReleaseMask |
		ButtonPress | ButtonReleaseMask |
		PointerMotionMask |
		StructureNotifyMask | SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, w, h, 0, vi->depth,
		InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	set_title();
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
}

void X11_wrapper::set_title()
{
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "3350 waterlab6");
}

bool X11_wrapper::getXPending()
{
	//See if there are pending events.
	return XPending(dpy);
}

XEvent X11_wrapper::getXNextEvent()
{
	//Get a pending event.
	XEvent e;
	XNextEvent(dpy, &e);
	return e;
}

void X11_wrapper::swapBuffers()
{
	glXSwapBuffers(dpy, win);
}

void X11_wrapper::reshape_window(int width, int height)
{
	//Window has been resized.
	g.xres = width;
	g.yres = height;
	//
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glOrtho(0, g.xres, 0, g.yres, -1, 1);
}

void X11_wrapper::check_resize(XEvent *e)
{
	//The ConfigureNotify is sent by the
	//server if the window is resized.
	if (e->type != ConfigureNotify)
		return;
	XConfigureEvent xce = e->xconfigure;
	if (xce.width != g.xres || xce.height != g.yres) {
		//Window size did change.
		reshape_window(xce.width, xce.height);
		// Re-initialize box positions & sizes based on new dimensions
        init_box();
	}
}
//------------------------------------------------------------------------

void X11_wrapper::check_mouse(XEvent *e)
{
	static int savex = 0;
	static int savey = 0;

	//Weed out non-mouse events
	if (e->type != ButtonRelease &&
		e->type != ButtonPress &&
		e->type != MotionNotify) {
		//This is not a mouse event that we care about.
		return;
	}
	//
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button was pressed.
			int y = g.yres - e->xbutton.y;
			for (int i = 0; i<3; i++)
				make_particle(e->xbutton.x, y);
			return;
		}
		if (e->xbutton.button==3) {
			//Right button was pressed.
			return;
		}
	}
	if (e->type == MotionNotify) {
		//The mouse moved!
		if (savex != e->xbutton.x || savey != e->xbutton.y) {
			savex = e->xbutton.x;
			savey = e->xbutton.y;
			//Code placed here will execute whenever the mouse moves.

			 for (int i = 0; i<5; i++) 
			 	make_particle(savex, g.yres-savey);
		}
	}
}

int X11_wrapper::check_keys(XEvent *e)
{
	if (e->type != KeyPress && e->type != KeyRelease)
		return 0;
	int key = XLookupKeysym(&e->xkey, 0);
	if (e->type == KeyPress) {
		switch (key) {
			case XK_a:
				//the 'a' key was pressed
				break;
			case XK_Escape:
				//Escape key was pressed
				return 1;
		}
	}
	return 0;
}

void init_opengl(void)
{
	//OpenGL initialization
	glViewport(0, 0, g.xres, g.yres);
	//Initialize matrices
    //
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    //Set 2D mode (no perspective)
	glOrtho(0, g.xres, 0, g.yres, -1, 1);
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
    //Set the screen background color
	glClearColor(0.3, 0.1, 0.1, 1.0);
	// Original values: (r)0.1, (g)0.1, (b)0.1, (transparency?)1.0

	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
}

const float GRAVITY = -0.2;

void physics()
{
	for (int i = 0; i<n; i++) {
		Box *p = &particles[i];
		p->prev[0] = p->pos[0];
		p->prev[1] = p->pos[1];
		// move particles
		p->force[1] = GRAVITY;
		p->vel[1] += p->force[1];
		p->vel[0] += p->force[0];
		p->pos[1] += p->vel[1];
		p->pos[0] += p->vel[0];
		p->force[1] = 0.0f;
		p->force[0] = 0.0f;

		// Collision detection with all boxes
        for (int j = 0; j < NUM_BOXES; j++) {
            Box *b = &boxes[j];
            // Simple collision check
            if (p->pos[0] >= (b->pos[0] - b->width) &&
                p->pos[0] <= (b->pos[0] + b->width) &&
                p->pos[1] >= (b->pos[1] - b->height) &&
                p->pos[1] <= (b->pos[1] + b->height)) 
            {
                // 60% of the speed is retained
                // p->pos[0] = p->prev[0];
                p->pos[1] = p->prev[1];
				// vertical bounce
                p->vel[1] = -p->vel[1] * 0.6f;
				// constant speed to the right
				p->vel[0] = 0.7f;              
                //  horizontal push to let it slide off
                p->vel[0] += 0.06f;
            }
        }

		if (p->pos[1] < -4.0f)
			delete_particle(i);
	}
}

void render()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	 // Draw the 5 Waterfall boxes
    for (int i = 0; i < NUM_BOXES; i++) {
        glPushMatrix();
        glColor3fv(boxes[i].color);
        glTranslatef(boxes[i].pos[0], boxes[i].pos[1], 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(-boxes[i].width, -boxes[i].height);
            glVertex2f(-boxes[i].width,  boxes[i].height);
            glVertex2f( boxes[i].width,  boxes[i].height);
            glVertex2f( boxes[i].width, -boxes[i].height);
        glEnd();
        glPopMatrix();

        // print text labels onto each box
        Rect r;
        r.left = (int)boxes[i].pos[0] - 46;
        r.bot  = (int)boxes[i].pos[1] - 5;
        r.center = 0;
        ggprint16(&r, 12, 0x00ffffff, boxes[i].text);
    }
	
	//draw all the particles
	for (int i = 0; i < n; i++){
		glPushMatrix();
		glColor3ub(4, 118, 208);
		Box *p = &particles[i];
		glTranslatef(p->pos[0], p->pos[1], 0.0f);
		glBegin(GL_QUADS);
			glVertex2f(-p->width, -p->height);
			glVertex2f(-p->width,  p->height);
			glVertex2f( p->width,  p->height);
			glVertex2f( p->width, -p->height);
		glEnd();
		glPopMatrix();
	}	
	Rect r;
	//
	r.bot = g.yres - 25;
	r.left = 10;
	r.center = 0;
	ggprint16(&r, 16, 0x00ff0000, "3350 - lab-6");
	ggprint16(&r, 16, 0x00ffff00, "The Waterfall Model");
}
