/*
 Edited by: Christian Rodriguez
 original author:  Gordon Griesel
            date:  Jan 23, 2025
         purpose:  C program for students to practice their C programming
                   over the Winter break. Also, introduce students to the
                   X Window System. We will use the X Window protocol or
                   API to generate output in some of our lab and homework
                   assignments.

 Instructions:

      1. If you make changes to this file, put your name at the top of
         the file. Use one C style multi-line comment to hold your full
         name. Do not remove the original author's name from this or 
         other source files please.

      2. Build and run this program by using the provided Makefile.

         At the command-line enter make.
         Run the program by entering ./a.out
         Quit the program by pressing Esc.

         The compile line will look like this:
            gcc xwin89.c -Wall -Wextra -Werror -pedantic -ansi -lX11

         To run this program on the Odin server, you will have to log in
         using the -YC option. Example: ssh myname@odin.cs.csub.edu -YC

      3. See the assignment page associated with this program for more
         instructions.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <unistd.h>

struct Global {
    Display *dpy;
    Window win;
    GC gc;
    int xres, yres;
} g;

void x11_cleanup_xwindows(void);
void x11_init_xwindows(void);
void x11_clear_window(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void render(void);
void changeColor(void);

#define NCORES 21
float use[NCORES];
float bar_width[NCORES];

int main(void)
{
    XEvent e;
    long total[NCORES];
    long idle[NCORES];
    long prev_total[NCORES];
    long prev_idle[NCORES];

    memset(total, 0, sizeof(long)*NCORES);
    memset(idle, 0, sizeof(long)*NCORES);
    memset(prev_total, 0, sizeof(long)*NCORES);
    memset(prev_idle, 0, sizeof(long)*NCORES);
    memset(use, 0, sizeof(float)*NCORES);

    int done = 0;
    x11_init_xwindows();
    while (!done) {
        /* Check the event queue */
        while (XPending(g.dpy)) {
            XNextEvent(g.dpy, &e);
            check_mouse(&e);
            done = check_keys(&e);
            render();
        }
        // usleep(4000);
        
        /* Phase start Class code*/
        
        usleep(4000);
        //get the /proc/stat file
        usleep(500000);
        FILE *fpi = fopen("/proc/stat", "r");
        if (fpi) {
            for (int core=0; core<NCORES; core++) {
                char str[100];
                fscanf(fpi, "%s", str);
                int i;
                prev_total[core] = total[core];
                prev_idle[core] = idle[core];
                total[core] = 0;
                for (i=0; i<10; i++) {
                    fscanf(fpi, "%s", str);
                    total[core] += atol(str);
                    if (i == 3)
                        idle[core] = atol(str);
                }
                float tdiff = total[core] - prev_total[core];
                float idiff = idle[core] - prev_idle[core];
                use[core] = (float)idiff / (float)tdiff;
                use[core] = (1.0f - use[core]) * 100.0f;
                render();
            }
            fclose(fpi);
        } else {
            perror("Failed to open /proc/stat");
            return 1;
        }


        /*End of phase start class code*/
    }
    x11_cleanup_xwindows();
    return 0;
}

void x11_cleanup_xwindows(void)
{
    XDestroyWindow(g.dpy, g.win);
    XCloseDisplay(g.dpy);
}

void x11_init_xwindows(void)
{
    int scr;

    if (!(g.dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "ERROR: could not open display!\n");
        exit(EXIT_FAILURE);
    }
    scr = DefaultScreen(g.dpy);
    g.xres = 350;
    g.yres = 500;
    g.win = XCreateSimpleWindow(g.dpy, RootWindow(g.dpy, scr), 1, 1,
                            g.xres, g.yres, 0, 0x00ffffff, 0x00000000);
    XStoreName(g.dpy, g.win, "cs3600 xwin sample");
    g.gc = XCreateGC(g.dpy, g.win, 0, NULL);
    XMapWindow(g.dpy, g.win);
    XSelectInput(g.dpy, g.win, ExposureMask | StructureNotifyMask |
                                PointerMotionMask | ButtonPressMask |
                                ButtonReleaseMask | KeyPressMask);
}

void check_mouse(XEvent *e)
{
    static int savex = 0;
    static int savey = 0;
    int mx = e->xbutton.x;
    int my = e->xbutton.y;

    if (e->type != ButtonPress
        && e->type != ButtonRelease
        && e->type != MotionNotify)
        return;
    if (e->type == ButtonPress) {
        if (e->xbutton.button==1) { }
        if (e->xbutton.button==3) { }
    }
    if (e->type == MotionNotify) {
        if (savex != mx || savey != my) {
            /*mouse moved*/
            savex = mx;
            savey = my;
            // write(1, "m", 1);
        }
    }
}

int check_keys(XEvent *e)
{
    int key;
    if (e->type != KeyPress && e->type != KeyRelease)
        return 0;
    key = XLookupKeysym(&e->xkey, 0);
    if (e->type == KeyPress) {
        switch (key) {
            case XK_1:
                break;
            case XK_a:
                // write(1, "a", 1);
                break;
            case XK_Escape:
                return 1;
        }
    }
    return 0;
}

void render(void)
{
    XSetForeground(g.dpy, g.gc, 0xFFC72C);
    XFillRectangle(g.dpy, g.win, g.gc, 0, 0, g.xres, g.yres);
    XFlush(g.dpy);

    XSetFont(g.dpy, g.gc, XLoadFont(g.dpy, "9x15bold"));
    XSetForeground(g.dpy, g.gc, 0x000000);

    char str[100];
    sprintf(str, "CPU Usage: ");
    XDrawString(g.dpy, g.win, g.gc, 10, 50, str, strlen(str));

    int barH = 12;
    int yOff = 70;

    int xBar = 80;                   // <-- start of the bar
    int maxW = g.xres - xBar;        // <-- how wide the bar can grow

    for (int i = 0; i < NCORES; i++) {
        float u = use[i];
        if (u < 0.0f) u = 0.0f;
        if (u > 100.0f) u = 100.0f;

        float target = (u / 100.0f) * maxW;
        bar_width[i] += 0.2f * (target - bar_width[i]);   // 0.2 = smoothing factor
        if (bar_width[i] < 0)
            bar_width[i] = 0;
        if (bar_width[i] > maxW)
            bar_width[i] = maxW;
        sprintf(str, "CPU %i: ", i);
        XDrawString(g.dpy, g.win, g.gc, 10, yOff, str, strlen(str));

        XSetForeground(g.dpy, g.gc, 0xFF0000);
        XFillRectangle(g.dpy, g.win, g.gc, xBar, yOff - barH + 3,
                    (int)(bar_width[i] + 0.5f), barH);
        XSetForeground(g.dpy, g.gc, 0x000000);

        yOff += 20;
    }
}


void changeColor(void) {
    XSetForeground(g.dpy, g.gc, 0x003594);
    XFillRectangle(g.dpy, g.win, g.gc, 0, 0, g.xres, g.yres);
    XFlush(g.dpy);
}





