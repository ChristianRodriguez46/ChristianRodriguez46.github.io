//modified by:
//date:
//
//author: Gordon Griesel
//date: Fall 2023
//purpose: 1. learn OpenGL
//         2. write an aerospace related program
//         3. prepare to apply for a job at SpaceX
//
//This is a game in which we try to land the rocket booster back on
//the launch pad. You must add code to check for a good landing, and
//also show the rocket landed and secure on the pad.
//
//If the rocket doesn't land safely, then you can show some kind of
//explosion or whatever.
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

//floating point random numbers
#define rnd() (float)rand() / (float)RAND_MAX

const double EPSILON = 0.0001;
//gravity pulling the rocket straight down
const float GRAVITY = 0.006;

class Global {
public:
	int xres, yres;
	unsigned int keys[65536];
	int failed_landing;
	int good_landing;
	int autopilot;
	//
    int crash_anim;
    float crash_color[3];
    double crash_radius;
    double crash_ang;
	int landing_points;
	int *horizon;
	int logo;
	int logo_frames;
	float spacex;
	float spacey;
	float spacey_vel;
	float spacex_intensity;
	int spacex_message;
	unsigned int space_col;
	int landing_timer;
	Global() {
		xres = 400;
		yres = 800;
		autopilot = 0;
		failed_landing = 0;
		good_landing = 0;
		landing_points = 0;
		landing_timer = 0;
		//
        crash_anim = 0;
        crash_color[0] = 0.1;
        crash_color[1] = 0.2;
        crash_color[2] = 0.0;
        crash_ang = 0.2;
        crash_radius = 0.1;
		horizon = new int[xres];
		srand(time(NULL));
		horizon[0] = 160;
		for (int i=1; i<xres; i++) {
			horizon[i] = horizon[i-1] + rand() % 3 - 1;
		}
		logo = 1;
		logo_frames = 0;
		spacex = 60.0f;
		spacey = yres + 2.0f;
		spacey_vel = -20.0f;
		space_col = 0x00ff0000;
		spacex_intensity = 0.0f;
		spacex_message = 0;
	}
} g;

class Lz {
	//landing zone
	public:
	float pos[2];
	float width;
	float height;
	Lz() {
		init();
	}
	void init() {
		pos[0] = g.xres / 2 + (rnd() * 340.0 - 170.0);
		pos[1] = 20.0f;
		width =  40.0f;
		height =  8.0f;
	}
} lz;

class Lander {
	//the rocket
	public:
	float pos[2];
	float vel[2];
	float verts[16][2];
	int nverts;
	float thrust;
	float thrust2;
	double angle;
	double thrust_angle;
	float leg_verts[16][2];
	int nleg_verts;
	double leg_angle;
	int leg_anim;
	int legs_are_down;
	Lander() {
		init();
	}
	void init() {
		pos[0] = 200.0f;
		pos[1] = g.yres - 60.0f;
		vel[0] = rnd() *  1.0f - 0.5f;
		vel[1] = rnd() * -0.5f;
		//3 vertices of triangle-shaped rocket lander
		nverts = 3;
		verts[0][0] = -10.0f;
		verts[0][1] =   0.0f;
		verts[1][0] =   0.0f;
		verts[1][1] =  30.0f;
		verts[2][0] =  10.0f;
		verts[2][1] =   0.0f;
		//4 vertices of booster-shaped lander
		float booster_height = 80.0f;
		nverts = 4;
		verts[0][0] = -8.0f;
		verts[0][1] =  0.0f;
		verts[1][0] = -8.0f;
		verts[1][1] =  booster_height;
		verts[2][0] =  8.0f;
		verts[2][1] =  booster_height;
		verts[3][0] =  8.0f;
		verts[3][1] =  0.0f;
		angle = 0.0;
		thrust_angle = 0.0;
		thrust = 0.0f;
		g.failed_landing = 0;
		g.good_landing = 0;
		//4 vertices of legs
		nleg_verts = 4;
		leg_verts[0][0] = -2.0f;
		leg_verts[0][1] =  0.0f;
		leg_verts[1][0] = -2.0f;
		leg_verts[1][1] =  30;
		leg_verts[2][0] =  2.0f;
		leg_verts[2][1] =  30;
		leg_verts[3][0] =  2.0f;
		leg_verts[3][1] =  0.0f;
		//angle is in degrees
		leg_angle = 0.0;
		leg_anim = 0;
		legs_are_down = 0;
	}
} lander;

unsigned char spacex_logo[30*11] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  1, 59,126,148,131,110,101, 52, 48, 12,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  7,121,177,199,190,165,103,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64,157,
211,234,197,135, 14,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11,147,212,250,219,
150, 23,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
167,252,253,248,160,  0,  0,  0, 65,177,239,252,205,110,  1,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,131,238,253,253,202, 63,185,246,253,210,104,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0, 62,205,196,182,244,253,233,132,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,110,227,253,253,194,177, 53,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,170,249,253,241,154,235,253,234,117,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
 51,207,253,253,227, 88,  0,168,248,253,250,179,  6,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
217,253,253,219, 56,  0,  0,  0,104,228,253,253,222, 52,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

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

//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0; 
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown;
double timeSpan;
double timeDiff(struct timespec *start, struct timespec *end);
void timeCopy(struct timespec *dest, struct timespec *source);
double timeDiff(struct timespec *start, struct timespec *end)
{
    //return the difference in two times.
    return (double)(end->tv_sec - start->tv_sec ) +
        (double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source)
{
    //copy one time structure to another.
    memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------


//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
int main()
{
	init_opengl();
	srand(time(NULL));
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	printf("Press T or Up-arrow for thrust.\n");
	printf("Press Left or Right arrows for rocket thrust vector.\n");
	//Main loop
	int done = 0;
	while (!done) {
		//Process external events.
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.check_resize(&e);
			x11.check_mouse(&e);
			done = x11.check_keys(&e);
		}
		//physics();
		// timers are used here to keep physics at a constant frame rate
		clock_gettime(CLOCK_REALTIME, &timeCurrent);
		timeSpan = timeDiff(&timeStart, &timeCurrent);
		timeCopy(&timeStart, &timeCurrent);
		physicsCountdown += timeSpan;
		while (physicsCountdown >= physicsRate) {
			physics();
			physicsCountdown -= physicsRate;
		}
		render();
		x11.swapBuffers();
		usleep(400);
	}
    cleanup_fonts();
	return 0;
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
	XStoreName(dpy, win, "3350 Space X Booster Challenge");
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
	//window has been resized.
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
	}
}
//-----------------------------------------------------------------------------

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
			//int y = g.yres - e->xbutton.y;
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


		}
	}
}

int X11_wrapper::check_keys(XEvent *e)
{
	if (e->type != KeyPress && e->type != KeyRelease)
		return 0;
	int key = XLookupKeysym(&e->xkey, 0);
	if (e->type == KeyPress)
		g.keys[key] = 1;
	if (e->type == KeyRelease)
		g.keys[key] = 0;
	if (e->type == KeyPress) {
		switch (key) {
			case XK_a:
				//Engage the auto pilot to land the booster.
				//
				g.autopilot = !g.autopilot; 
				break;
			case XK_i:
				//Key I was pressed
				//show the animated intro again
				g.logo = 1;
				g.logo_frames = 0;
				g.spacex = 60.0f;
				g.spacey = g.yres + 2.0f;
				g.spacey_vel = -20.0f;
				g.space_col = 0x00ff0000;
				g.spacex_message = 0;
				g.spacex_intensity = 0.0f;
				break;
			case XK_f:
				//Key F was pressed
				g.logo = 0;
				lander.init();
				lz.init();
				break;
			case XK_r:
				//Key R was pressed
				lander.init();
				lz.init();
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
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//Set 2D mode (no perspective)
	glOrtho(0, g.xres, 0, g.yres, -1, 1);
	//Set the screen background color
	glClearColor(0.0, 0.0, 0.0, 1.0);
    //Do this to allow fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();
}
void autoPilotControl(void);

/* -------------------------------------------------------------- *
 * position-based auto-pilot                   *
 * – lateral error → desired vx; attitude + side-thrust correct   *
 * – altitude error → desired vy; pulsed main engine brakes       *
 * -------------------------------------------------------------- */
void autoPilotControl(void)
{
	/* persistent timer for main-engine pulses */
	static int pulse = 0;

	/* ---- tunables ------------------------------------------------ */
	const float ANG  = 15.0f;          /* vector angle               */
	const float PWR  = 0.005f;         /* side-engine power          */
	const float MAIN = 0.01f;          /* main-engine pulse power    */

	/* ---- desired velocities from position errors ---------------- */
	float vx_des = (lz.pos[0] - lander.pos[0]) / 300.0f;
	float vy_des = (lz.pos[1] - lander.pos[1]) / 400.0f;

	/* ---- lateral closed loop ------------------------------------ */
	float vx_err = vx_des - lander.vel[0];

	/* steer until velocity matches; then straighten body */
	if (vx_err < -0.01f && lander.angle <  ANG) {
		lander.thrust2      = PWR;
		lander.thrust_angle = -ANG;
		lander.angle       += 0.5f;
	}
	if (vx_err >  0.01f && lander.angle > -ANG) {
		lander.thrust2      = PWR;
		lander.thrust_angle =  ANG;
		lander.angle       -= 0.5f;
	}
	if (fabsf(vx_err) < 0.01f && fabsf(lander.angle) < 0.5f)
		lander.angle = 0.0f;           /* snap upright */

	/* ---- vertical pulse controller ------------------------------ */
	pulse++;
	/* bigger velocity error ⇒ smaller rate (more frequent burns) */
	int rate = (int)(1.0f /
			fmaxf(fabsf(vy_des - lander.vel[1]), 0.01f));
	if (pulse >= rate && lander.vel[1] < vy_des) {
		lander.thrust = MAIN;          /* one-frame burn             */
		pulse = 0;
	}
}
 
void physics()
{
	if (g.autopilot == 1) {
		autoPilotControl();
	}
	//Animated intro movement...
	if (g.logo) {
		g.spacex_intensity += 0.015f;
		if (g.spacex_intensity > 1.0f)
			g.spacex_intensity = 1.0f;
		//falling...
		g.spacey += g.spacey_vel; 
		//gradually slow down the descent
		g.spacey_vel *= 0.94f;
		//stop in position
		if (g.spacey <= 400.0f + 10.0f * 8.0f) {
			g.spacey = 400.0f + 10.0f * 8.0f;
			g.space_col = 0x00ddddff;
			//We can use frame count as a timer because
			//physics() is called at a constant rate.
			if (++g.logo_frames > 60) {
				//1-second has passed.
				g.spacex_message = 1;
			}
		}
	}
	//
	//Lander physics
	if (g.good_landing) {
		//If booster is sitting on pad for a few seconsd, reset.
		if ((g.landing_timer + 3) < time(NULL)) {
			//Reset
			lander.init();
			lz.init();
		}
		return;
	}
	if (g.failed_landing) {
        if (g.crash_anim) {
            g.crash_radius += 0.5;
            g.crash_color[0] = sin(g.crash_ang);
            g.crash_ang += 0.01;
            if (g.crash_ang >= 3.14 * 1.0)
                g.crash_anim = 0;
        }
		//If booster is sitting for a few seconsd, reset.
		if ((g.landing_timer + 2) < time(NULL)) {
			//Reset
			lander.init();
			lz.init();
		}
        return;
    }
	//
	//Deploy lander legs?
	if (lander.pos[1] < g.yres / 4) {
		if (lander.vel[1] < 0.0 && lander.vel[1] > -0.4)
			lander.leg_anim = 1;
	}
	if (lander.vel[1] > 0.15) {
		lander.leg_anim = 2;
	}
	if (lander.leg_anim == 1) {
		lander.leg_angle += 1.5;
		if (lander.leg_angle >= 150.0) {
			lander.leg_angle = 150.0;
			lander.leg_anim = 0;
			lander.legs_are_down = 1;
		}
	}
	if (lander.leg_anim == 2) {
		lander.legs_are_down = 0;
		lander.leg_angle -= 1.5;
		if (lander.leg_angle <= 0.0) {
			lander.leg_angle = 0.0;
			lander.leg_anim = 0;
		}
	}
	//
	//Move the lander
	lander.pos[0] += lander.vel[0];
	lander.pos[1] += lander.vel[1];
	lander.vel[1] -= GRAVITY;
	//apply thrust
	//convert angle to radians...
	float ang = ((lander.angle+90.0) / 360.0) * (3.14159 * 2.0);
	//make a thrust vector...
	float xthrust = cos(ang) * lander.thrust;
	float ythrust = sin(ang) * lander.thrust;
	lander.vel[0] += xthrust;
	lander.vel[1] += ythrust;
	lander.thrust *= 0.95f;
	lander.thrust_angle *= 0.96f;
	lander.thrust2 *= 0.91f;
	if (lander.thrust < EPSILON)
		lander.thrust = 0.0;
	if (lander.thrust2 < EPSILON)
		lander.thrust2 = 0.0;
	if (lander.thrust_angle < EPSILON)
		lander.thrust_angle = 0.0;
	//
	//Check for keys being held down...
	if (g.keys[XK_t] || g.keys[XK_Up]) {
		//Thrust for the rocket
		lander.thrust = 0.01;
	}
	if (g.keys[XK_Left]) {
		lander.thrust2 = 0.005;
		lander.thrust_angle = -15.0;
		lander.angle += 0.5;
	}
	if (g.keys[XK_Right]) {
		lander.thrust2 = 0.005;
		lander.thrust_angle = 15.0;
		lander.angle -= 0.5;
	}
	//
	//check for landing failure...
	if (lander.pos[1] < lz.pos[1]) {
		g.failed_landing = 1;
		g.landing_timer = time(NULL);
        g.crash_anim = 1;
        g.crash_radius = 0.0;
        g.crash_ang = 0.0;
		lander.thrust = 0.0;
	}
	//
	// Did the lander land safely?
	// In-line with the LZ?
	if (lander.pos[0] >= lz.pos[0] - lz.width &&
						lander.pos[0] <= lz.pos[0] + lz.width) {
		// Yes, in-line with LZ
		// Did the lander drop below the top of the pad?
		if (lander.pos[1] < lz.pos[1] + lz.height) {
			// Yes below the top of the pad.
			// Is the downward velocity slow enough for a good landing?
			if (lander.vel[1] > -0.2 && fabs(lander.vel[0]) < 0.2) {
				// Yes, slow enough.
				// Are the legs fully deployed?
				if (lander.legs_are_down) {
					g.good_landing = 1;
					g.landing_timer = time(NULL);
					int off_center = lz.pos[0] - lander.pos[0];
					off_center = abs(off_center);
					g.landing_points += 100 - off_center;
					lander.thrust = 0.0;
					lander.angle = 0.0;
				}
			}
		}
	}
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//
	//Draw animated intro...
	if (g.logo) {
		unsigned char c;
		int x = 60;
		int y = 400 + 11*10;
		glBegin(GL_QUADS);
			int idx = 0;
			for (int i=0; i<11; i++) {
				for (int j=0; j<30; j++) {
					c = spacex_logo[idx++];
					c = (int)((float)c * g.spacex_intensity);
					glColor3ub(c, c, c);
					glVertex2i(x,    y);
					glVertex2i(x+10, y);
					glVertex2i(x+10, y+10);
					glVertex2i(x,    y+10);
					x += 10;
				}
				y -= 10;
				x = 60;
			}
		glEnd();
		Rect r;
		r.bot = g.spacey;
		r.left = g.spacex;
		r.center = 0;
		ggprint8b(&r, 20, g.space_col, "S P A C E");
		if (g.spacex_message) {
			//Show a message to press a key
			r.bot = g.spacey + 6 * 10 + 20;
			r.left = g.xres / 2 - 80;
			r.left = g.spacex;
			r.center = 0;
			ggprint8b(&r, 20, g.space_col, "P R E S S  ' F '  T O  F L Y !");
		}
		return;
	}
	//
	//Draw sky
	glPushMatrix();
	glBegin(GL_QUADS);
		//Each vertex has a color.
		glColor3ub(250, 200,  90); glVertex2i(0, 0);
		glColor3ub(100,  80, 200); glVertex2i(0, g.yres);
		glColor3ub(100,  80, 200); glVertex2i(g.xres, g.yres);
		glColor3ub(250, 200,  90); glVertex2i(g.xres, 0);
	glEnd();
	glPopMatrix();
	//
	//Draw a horizon
	for (int i=0; i<g.xres; i++) {
		float re = .850;
		float gr = .680;
		float bl = .440;
		glBegin(GL_LINES);
			glColor3f(re*0.7f, gr*0.7f, bl*0.7f);
			glVertex2i(i, g.horizon[i]);
			glColor3f(re*0.95f, gr*0.95f, bl*0.95f);
			glVertex2i(i, 0);
		glEnd();
	}
	//
	//Draw LZ
	glPushMatrix();
	glColor3ub(250, 250, 20);
	glTranslatef(lz.pos[0], lz.pos[1], 0.0f);
	glBegin(GL_QUADS);
		glVertex2f(-lz.width, -lz.height);
		glVertex2f(-lz.width,  lz.height);
		glVertex2f( lz.width,  lz.height);
		glVertex2f( lz.width, -lz.height);
	glEnd();
	glPopMatrix();
	//
    //Draw crash before drawing lander
    if (g.failed_landing && g.crash_anim) {
        glPushMatrix();
        //show crash graphics here...
        //draw lines going out from lander
        glColor3fv(g.crash_color);
        glTranslatef(lander.pos[0], lander.pos[1], 0.0f);
        int n = 100;
        for (int i=0; i<n; i++) {
            //random angle between 0.0 and pi*2
            double ang = rnd();
            ang *= 3.14159265358979;
            ang *= 2;
            double x = cos(ang);
            double y = sin(ang);
            x = x * g.crash_radius;
            y = y * g.crash_radius;
            glLineWidth(2.0);
            glBegin(GL_LINES);
                glVertex2f(rnd()*12.0 - 6.0, rnd() * 12.0 - 6.0);
                glVertex2f((float)x+rnd()*20.0-10.0, (float)y+rnd()*20.0-10.0);
            glEnd();
        }
        glPopMatrix();
    }
	//
	//Draw Lander
	glPushMatrix();
	glColor3ub(50, 50, 50);
	if (g.failed_landing)
 		glColor3ub(250, 0, 0);
	glTranslatef(lander.pos[0], lander.pos[1], 0.0f);
	glRotated(lander.angle, 0.0, 0.0, 1.0);
	if (lander.nverts == 3) {
		glBegin(GL_TRIANGLES);
		for (int i=0; i<3; i++) {
			glVertex2f(lander.verts[i][0], lander.verts[i][1]);
		}
		glEnd();
	}
	if (lander.nverts == 4) {
		glBegin(GL_QUADS);
		for (int i=0; i<4; i++) {
			glVertex2f(lander.verts[i][0], lander.verts[i][1]);
		}
		glEnd();
	}
	//Draw right leg
	glPushMatrix();
	glColor3ub(30, 30, 30);
	glTranslatef(6.0, lander.leg_verts[1][1]-5.0, 0.0f);
	glRotated(-lander.leg_angle, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		for (int i=0; i<4; i++) {
			glVertex2f(lander.leg_verts[i][0], lander.leg_verts[i][1]);
		}
	glEnd();
	glPopMatrix();
	//Draw left leg
	glPushMatrix();
	glColor3ub(30, 30, 30);
	glTranslatef(-6.0, lander.leg_verts[1][1]-5.0, 0.0f);
	glRotated(lander.leg_angle, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		for (int i=0; i<4; i++) {
			glVertex2f(lander.leg_verts[i][0], lander.leg_verts[i][1]);
		}
	glEnd();
	glPopMatrix();
	//
	//Lander thrust
	if (lander.thrust > 0.0 || lander.thrust2 > 0.0) {
		//Draw the thrust vector, aligned with the rocket angle.
		glBegin(GL_LINES);
			for (int i=0; i<25; i++) {
				glColor3ub(0, 0, 255);
				glVertex2f(rnd()*10.0-5.0, 0.0);
				glColor3ub(250, 150, 0);
				glVertex2f(0.0+rnd()*14.0-7.0,
					lander.thrust * (-4000.0 - rnd() * 2000.0));
			}
		glEnd();
		//Draw the thrust vector
		//Rotate to show rocket engine is vectoring thrust.
		glPushMatrix();
		glRotated(lander.thrust_angle, 0.0, 0.0, 1.0);
		glBegin(GL_LINES);
			for (int i=0; i<25; i++) {
				glColor3ub(0, 0, 255);
				glVertex2f(rnd()*10.0-5.0, 0.0);
				glColor3ub(250, 150, 0);
				glVertex2f(0.0+rnd()*14.0-7.0,
					lander.thrust2 * (-4000.0 - rnd() * 2000.0));
			}
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	//
	//Show other crash graphics
	if (g.failed_landing) {
		//none yet
			   
	}
	//
	//Draw a menu
	Rect r;
	r.bot = g.yres - 16;
	r.left = 8;
	r.center = 0;
	ggprint8b(&r, 20, 0x00000000, "Space-X Booster landing");
	ggprint8b(&r, 16, 0x00ffffff, "A     - Auto Pilot");
	ggprint8b(&r, 16, 0x00ffffff, "I     - Animated intro");
	ggprint8b(&r, 16, 0x00ffffff, "R     - Reset");
	ggprint8b(&r, 16, 0x00ffffff, "Up    - Thrust");
	ggprint8b(&r, 16, 0x00ffffff, "Left  - Vector Thrust");
	ggprint8b(&r, 16, 0x00ffffff, "Right - Vector Thrust");
	//ggprint8b(&r, 16, 0x00000000, "Landings: %i", g.nlandings);
	//ggprint8b(&r, 16, 0x00000000, "Crashes:  %i", g.ncrashes);
}

