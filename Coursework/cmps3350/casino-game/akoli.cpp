// Phillip Lakes (Koli)
// CS 3350 Software Engineering
// Slot Machine
// 03/03/2025
// g++ main.cpp akoli.cpp -o slot -Wall -lX11 -lGLU -lm -lGL
// "There is only one good, knowledge, and one evil, ignorance." - Socrates
//
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "include/fonts.h"
#include "time.h"
#include "include/phil_funcs.h"
#include "include/image.h"
#include "include/reel.h"
#include "include/global.h"
#include "include/x11.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>
#include <map>
#include <array>
#include <chrono>

std::chrono::time_point<std::chrono::high_resolution_clock>
last_time = std::chrono::high_resolution_clock::now();

Surface *surface;

GLUquadricObj *quadratic;	// Storage object
GLuint cylinder_side_tex;
GLuint cylinder_spinner_tex;
GLuint reels_tex;
GLuint slot_face_tex;

GLfloat L_Ambient[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat L_Diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat L_Pos[] = { 0.0f, 0.0f, 2.0f, 1.0f };

void calculate_framerate();
bool blink_state = true;
time_t last_blink_time = time(nullptr);
void quit(int retcode);
GLfloat get_rand(GLfloat max);
Surface *loadPNG(const char *fp);
bool initGLTexture(const char *name, GLuint *addr);
bool isWinner = false;
bool IRS;
int loadGLTextures();
int initGL(GLvoid);
int resize(int width, int height);
void drawReels();
int draw(GLvoid);

void calculate_framerate()
{
	auto current_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> elapsed = current_time - last_time;
	last_time = current_time;
	float fps = 1.0f / elapsed.count();
	std::cout << "FPS: " << fps << std::endl;
}

void quit(int retcode)
{
	gluDeleteQuadric(quadratic);
	glDeleteTextures(1, &cylinder_side_tex);
	glDeleteTextures(1, &cylinder_spinner_tex);
	glDeleteTextures(1, &reels_tex);
	glDeleteTextures(1, &slot_face_tex);
	exit(retcode);
}

Surface *loadPNG(const char *fp)
{
	Image img(fp);
	if (!img.data) {
		std::cerr << "Error: Failed to load image: " << fp << std::endl;
		return nullptr;
	}
	surface = new Surface();
	surface->width = img.width;
	surface->height = img.height;
	surface->data = new unsigned char[img.width * img.height * 3];
	std::memcpy(surface->data, img.data, img.width * img.height * 3);
	std::cout << "loadPNG(): " << fp << " (" << surface->width << "x"
		  << surface->height << ")\n";
	if (!surface) {
		fprintf(stderr, "No Surface!\n");
		quit(1);
	}
	return surface;
}

// reel.cpp
static int gluttony = -1;
struct Reel;
Reel *reels[3];

GLfloat get_rand(GLfloat max)
{
	return (1 + (float)(max * (rand() / (RAND_MAX + 1.0))));
}

Reel::Reel()
{
	//start();
}

void Reel::start()
{
	stopped = false;
	speed = get_rand(2);
	degree = get_rand(360);
	begin = 0;
	begin = speed;
	gluttony = -1;
	isWinner = false;
	IRS = true;
}

void Reel::stop()
{
	int r = 0;
	for (int x = 0; x < 3; ++x) {
		if (reels[x]->speed < reels[r]->speed) {
			r = x;
		}
	}
	reels[r]->stopped = true;
}

int Reel::winner()
{
	int win = reels[0]->position();
	for (int x = 1; x < 3; ++x) {
		if (win != reels[x]->position()) {
			return -1;
		}
	}
	return win;
}

int Reel::num_stopped()
{
	int num = 0;
	for (int x = 0; x < 3; ++x) {
		if (reels[x]->stopped) {
			++num;
		}
	}
	return num;
}

bool Reel::all_stopped()
{
	return (num_stopped() == 3);
}

int Reel::position()
{
	return static_cast<int>(roundf((degree - 30) / 40));
}

bool Reel::at_stop_position()
{
	return (static_cast<GLint>(roundf(degree + 10)) % 40 == 0);
}

int Reel::stop_position(Reel *reel)
{
	int position = reel->position();
	if (gluttony != -1) {
		return gluttony;
	}
	switch (Reel::num_stopped()) {
	case 0:
		return position;
	case 1:
		for (int x = 0; x < 3; ++x) {
			if (reels[x]->stopped) {
				return reels[x]->position();
			}
		}
		return position;
	default:
		int reel_stopped;
		for (int x = 0; x < 3; ++x) {
			if (reels[x]->stopped) {
				reel_stopped = reels[x]->position();
			}
		}
		int w = static_cast<int>(get_rand(3));
		std::cout << "A partial act of gluttony: " << (w == 1) << std::endl;
		if (w == 1) {
			return gluttony = reel_stopped;
		} else {
			if (position == reel_stopped) {
				if (++position > 9) {
					position = 0;
				}
			}
			return gluttony = position;
		}
	}
}

void Reel::spin()
{
	if (this->stopped) {
		return;
	}
	if (speed < 0.2) {
		if (this->at_stop_position()) {
			if (Reel::stop_position(this) == this->position()) {
				stopped = true;
				if (Reel::all_stopped()) {
					const std::array<std::string, 9> rSymbol = {
						"Cherry", "Ol' No.7", "Watermelon",
						"Diamond", "Horseshoe",
						"Bell", "3 BAR", "2 BAR", "BAR"
					};

					for (int i = 0; i < 3; ++i) {
						int position = reels[i]->position();
						if (position >= 0 &&
						    position < static_cast<int>(rSymbol.size())) {
							std::cout << "Reel halts on: "
								  << rSymbol[position] << std::endl;
						} else {
							std::cout << "Reel halts on: yomama"
								  << std::endl;
						}
					}

					std::cout << "################################"
						  << std::endl;
					int winner = Reel::winner();
					if (winner != -1) {
						isWinner = true;
						std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
							  << std::endl;
						std::cout << "```Behold the Ghetto Kingpin!```"
							  << std::endl;
						std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
							  << std::endl;
					}
				}
			}
		}
	} else {
		speed -= 0.005;
	}
	degree += speed;
	if (degree > 360) {
		degree -= 360;
	}
}

unsigned char* buildAlphaPData(Image* img)
{
    int width = img->width;
    int height = img->height;
    unsigned char* data = img->data;
    unsigned char* newdata = (unsigned char*)malloc(width * height * 4);
    unsigned char* ptr = newdata;

    for (int i = 0; i < width * height * 3; i += 3) {
        unsigned char r = data[i + 0];
        unsigned char g = data[i + 1];
        unsigned char b = data[i + 2];

        *ptr++ = r;
        *ptr++ = g;
        *ptr++ = b;

        // Make pure black (0,0,0) transparent, else fully opaque
        if (r == 0 && g == 0 && b == 0)
            *ptr++ = 0;
        else
            *ptr++ = 255;
    }

    return newdata;
}

bool initGLTexture(const char *name, GLuint *addr)
{
    Image img(name);
    if (!img.data) {
        std::cerr << "Failed to load: " << name << std::endl;
        return false;
    }

    unsigned char* rgba = buildAlphaPData(&img);

    glGenTextures(1, addr);
    glBindTexture(GL_TEXTURE_2D, *addr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);

    free(rgba);
    return true;
}

int loadGLTextures()
{
	initGLTexture("images/cyl_side_tex.png", &cylinder_side_tex);
	initGLTexture("images/cyl_spinner_tex.png", &cylinder_spinner_tex);
	initGLTexture("images/reels_tex.png", &reels_tex);
	initGLTexture("images/slot_face.png", &slot_face_tex);

	return 1;
}

int initGL(GLvoid)
{
	if (loadGLTextures() == 1) {
		std::cout << "loadGLTextures() success\n";
	}
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f/255.0f, 87.0f/255.0f, 173.0f/255.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glLineWidth(1.5);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);
	glLightfv(GL_LIGHT1, GL_AMBIENT, L_Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, L_Diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, L_Pos);
	glEnable(GL_LIGHT1);
	quadratic = gluNewQuadric();
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);
	return 1;
}

int resize(int width, int height)
{
	GLfloat ratio;
	if (height == 0) {
		height = 1;
	}
	ratio = GLfloat(width) / GLfloat(height);
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return 1;
}

void drawReels()
{
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glTranslatef(1.0f, -0.4f, -3.9);

	for (int x = 0; x < 3; ++x) {
		Reel *reel = reels[x];
		reel->spin();
	}

	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	glPushMatrix();
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -3.4f);
		glBindTexture(GL_TEXTURE_2D, cylinder_spinner_tex);
		gluCylinder(quadratic, 0.2f, 0.2f, 5.0f, 9, 3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(reels[0]->degree, 1.0f, 0.0f, 0.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -0.20f);
		glBindTexture(GL_TEXTURE_2D, cylinder_side_tex);
		gluDisk(quadratic, 0.2f, 1.0f, 9, 3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(reels[0]->degree, 1.0f, 0.0f, 0.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -0.20f);
		glBindTexture(GL_TEXTURE_2D, reels_tex);
		gluCylinder(quadratic, 1.0f, 1.0f, 0.7f, 9, 3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(reels[1]->degree, 1.0f, 0.0f, 0.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -1.38f);
		glBindTexture(GL_TEXTURE_2D, reels_tex);
		gluCylinder(quadratic, 1.0f, 1.0f, 0.7f, 9, 1);
	glPopMatrix();

	glPushMatrix();
		glRotatef(reels[2]->degree, 1.0f, 0.0f, 0.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -1.9f);
		glBindTexture(GL_TEXTURE_2D, cylinder_side_tex);
		gluDisk(quadratic, 0.2f, 1.0f, 9, 3);
	glPopMatrix();

	glPushMatrix();
		glRotatef(reels[2]->degree, 1.0f, 0.0f, 0.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -2.5f);
		glBindTexture(GL_TEXTURE_2D, reels_tex);
		gluCylinder(quadratic, 1.0f, 1.0f, 0.6f, 9, 3);
	glPopMatrix();
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
		std::cout << "\n\tcannot connect to X server\n" << std::endl;
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		std::cout << "\n\tno appropriate visual found\n" << std::endl;
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

void X11_wrapper::check_mouse(XEvent *e)
{
	static int savex = 0;
	static int savey = 0;

	if (e->type != ButtonRelease &&
	    e->type != ButtonPress &&
	    e->type != MotionNotify) {
		return;
	}
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button == 1) {
			return;
		}
		if (e->xbutton.button == 3) {
			return;
		}
	}
	if (e->type == MotionNotify) {
		if (savex != e->xbutton.x || savey != e->xbutton.y) {
			savex = e->xbutton.x;
			savey = e->xbutton.y;
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
		default:
			break;
		}
	}
	return 0;
}

void X11_wrapper::set_title()
{
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "Ghetto Casino - Slot Machine");
}

bool X11_wrapper::getXPending()
{
	return XPending(dpy);
}

XEvent X11_wrapper::getXNextEvent()
{
	XEvent e;
	XNextEvent(dpy, &e);
	return e;
}

void X11_wrapper::swapBuffers()
{
	glXSwapBuffers(dpy, win);
}

void updateBlinkState()
{
    time_t current_time = time(nullptr);
    blink_state = !blink_state;
    last_blink_time = current_time;
}

void slotface()
{
    glPushMatrix();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, slot_face_tex);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, g.xres, 0, g.yres, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.0f); // Bottom-left
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, g.yres); // Top-left
        glTexCoord2f(1.0f, 0.0f); glVertex2f(g.xres, g.yres); // Top-right
        glTexCoord2f(1.0f, 1.0f); glVertex2f(g.xres, 0.0f); // Bottom-right
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
}

int draw(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0f, 0.10f, 0.60f,  // Camera position
	          0.0f, 0.0f, 0.0f,  // Look-at point
	          0.0f, 1.0f, 0.0f); // Up vector

	drawReels();
	slotface();

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, g.xres, 0, g.yres, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	updateBlinkState();

	Rect r;
	r.bot = g.yres - 30;
	r.left = 10;
	r.center = 0;
	ggprint16(&r, 32, 0x00551705, "```Welcome to the Ghetto```");

	Rect r2;
	r2.bot = g.yres - 610;
	r2.left = 500;
	r2.center = 0;
	ggprint16(&r2, 32, 0x00ffffff, "Press SPACE to spin the reels!");

	Rect r3;
	r3.bot = g.yres - 500;
	r3.left = 1100;
	r3.center = 0;
	std::string str_obj = "Chips: " + std::to_string(g.currency);
	const char* chip_str = str_obj.c_str();
	ggprint16(&r3, 32, 0x00ffffff, chip_str);

	if (isWinner) {
		Rect x1;
		x1.bot = g.yres - 50;
		x1.left = 473;
		x1.center = 0;
		Rect x2;
		x2.bot = g.yres - 70;
		x2.left = 473;
		x2.center = 0;
		Rect x3;
		x3.bot = g.yres - 90;
		x3.left = 473;
		x3.center = 0;
		g.currency += 10;
		if (blink_state) {
			ggprint16(&x1, 32, 0x00ffff00, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
			ggprint16(&x2, 32, 0x00ffff00, "      ```Behold the Ghetto Kingpin!```");
			ggprint16(&x3, 32, 0x00ffff00, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
		}

	}
	else if (Reel::all_stopped()) {
		Rect x4;
		x4.bot = g.yres - 50;
		x4.left = 520;
		x4.center = 0;
		ggprint16(&x4, 32, 0x00ffff00, "         No se Jose!");
		if (IRS) {
			g.currency -= 5;
			IRS = false;
		}
	}

	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "OpenGL Error: " << gluErrorString(err) << std::endl;
	}

	return 1;
}
