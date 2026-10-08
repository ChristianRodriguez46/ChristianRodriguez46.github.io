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
#include <sys/wait.h>   /* for wait system call          */
#include <signal.h>     /* added: signals */
#include <time.h>       /* added: srand seed */

int changed = 0;  // <- used to check changed color
int child = 0;    // <- to know if window = child
int childActive;  // <- flag to know if CHILD is Active

/* added minimal state */
int xeyesActive = 0;                 /* track xeyes state */
pid_t child_pid = -1;         /* pid of our child window */
pid_t xeyes_pid = -1;         /* pid of xeyes */
unsigned long child_bg = 0x00ff0000; /* child background color */

struct Global {
    Display *dpy;
    Window win;
    GC gc;
    int xres, yres;
} g;

/* forward decls for child signal handlers and xeyes launcher */
void child_sigusr1(int sig);
void child_sigusr2(int sig);
void make_xeyes_window(void);

void myhandler(int sig)
{
    if (sig == SIGCHLD) {
        int status;
        /* determine which child window closed */
        pid_t p = waitpid(-1, &status, WUNTRACED | WNOHANG);
        if (p > 0) {
            if (p == child_pid) {
                childActive = 0;
                child_pid = -1;
            } else if (p == xeyes_pid) {
                xeyesActive = 0;
                xeyes_pid = -1;
            }
        }
        usleep(100000);
    }
}

void x11_cleanup_xwindows(void);
void x11_init_xwindows(void);
void x11_clear_window(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void render(void);
void changeColor(void);


char **myargv;
char **myenvp;

int main(int argc, char *argv[], char *envp[])
{
    myargv = argv;
    myenvp = envp;

    if (argc > 1) {
        if (strcmp(argv[1], "xxx-child-xxx") == 0)
            child = 1;
    }

    /* install signals */
    if (!child) {
        signal(SIGCHLD, myhandler);       /* parent: single handler */
    } else {
        srand((unsigned)(time(NULL) ^ getpid()));
        signal(SIGUSR1, child_sigusr1);   /* child: color change */
        signal(SIGUSR2, child_sigusr2);   /* child: terminate */
    }

    XEvent e;
    int done = 0;
    x11_init_xwindows();
    while (!done) {
        while (XPending(g.dpy)) {
            XNextEvent(g.dpy, &e);
            check_mouse(&e);
            done = check_keys(&e);
            render();
        }
        usleep(4000);
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
    g.xres = 400;
    g.yres = 200;
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
    int savex = 0;
    int savey = 0;
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
            write(1, child ? "c" :"m", 1);
        }
    }
}

void make_child_window() {
    childActive = 0;
    
    pid_t pid = fork();
    if (pid == 0) {
        // child

        /* Refactor the following three lines
            * child = 1;
            * main();
            * exit(0);
        * --------------*/
        // char *arg[] = {"/usr/bin/xeyes", NULL};
        // execve("/usr/bin/xeyes", arg, myenvp);
        char *arg[] = {myargv[0], "xxx-child-xxx", NULL};
        execve(arg[0], arg, myenvp);

    } else {
        // parent
        signal(SIGCHLD, myhandler);
        child_pid = pid;
        childActive = 1;
    }
}

/* added: xeyes launcher/toggler */
void make_xeyes_window(void)
{
    if (!xeyesActive) {
        pid_t p = fork();
        if (p == 0) {
            char *arg[] = {"/usr/bin/xeyes", NULL};
            execve("/usr/bin/xeyes", arg, myenvp);
            _exit(1);
        } else if (p > 0) {
            xeyes_pid = p;
            xeyesActive = 1;
        }
    } else {
        if (xeyes_pid > 0)
            kill(xeyes_pid, SIGTERM); /* close xeyes by signal */
        /* myhandler will flip xeyesActive to 0 on SIGCHLD */
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
            case XK_c:
                if (!childActive)
                    make_child_window();
                break;
            case XK_a:
                /* color-change request to child */
                if (!child && childActive && child_pid > 0)
                    kill(child_pid, SIGUSR1);
                write(1, "a", 1);
                break;
            case XK_b:
                /* close child */
                if (!child && childActive && child_pid > 0)
                    kill(child_pid, SIGUSR2);
                break;
            case XK_x:
                /* toggle xeyes */
                if (!child)
                    make_xeyes_window();
                break;
            case XK_Escape:
                return 1;
        }
    }
    return 0;
}

void render(void)
{
    /* Nothing being rendered yet. */
    XSetFont(g.dpy, g.gc, XLoadFont(g.dpy, "9x15bold"));

    XSetForeground(g.dpy, g.gc, !changed ? 0xFFC72C : 0x003594);
    XFillRectangle(g.dpy, g.win, g.gc, 0, 0, g.xres, g.yres);

    if (!child) {
        XSetForeground(g.dpy, g.gc, !changed ? 0x00000000: 0xffffffff);
        XDrawString(g.dpy, g.win, g.gc, 10,20, "I'm the parent", 14);

        if (!childActive) {
            XDrawString(g.dpy, g.win, g.gc, 10,40, "C - child window", 16);
        } else {
            XDrawString(g.dpy, g.win, g.gc, 10,40, "A - color change", 16);
            XDrawString(g.dpy, g.win, g.gc, 10,55, "B - close child", 15);
        }

        if (!xeyesActive) {
            XDrawString(g.dpy, g.win, g.gc, 10,75, "X - xeyes", 9);
        } else {
            XDrawString(g.dpy, g.win, g.gc, 10,75, "X - close xeyes", 15);
        }

        XDrawString(g.dpy, g.win, g.gc, 10,95, "Esc to exit", 11);

    } else {
        XSetForeground(g.dpy, g.gc, child_bg);
        XFillRectangle(g.dpy, g.win, g.gc, 0, 0, g.xres, g.yres);
        
        /* keep text readable against background */
        {
            int r = (int)((child_bg >> 16) & 0xff);
            int g2 = (int)((child_bg >> 8) & 0xff);
            int b = (int)(child_bg & 0xff);
            int lum = (299*r + 587*g2 + 114*b) / 1000;
            unsigned long txt = (lum >= 128) ? 0x000000 : 0xffffff;
            XSetForeground(g.dpy, g.gc, txt);
        }

        XDrawString(g.dpy, g.win, g.gc, 10,20, "I'm the child", 13);
    }
}


void changeColor(void) {
    XSetForeground(g.dpy, g.gc, 0x003594);
    XFillRectangle(g.dpy, g.win, g.gc, 0, 0, g.xres, g.yres);
    XFlush(g.dpy);
}

/* child signal handlers */

void child_sigusr1(int sig)
{
    usleep(100000);
    child_bg = (unsigned long)(rand() & 0x00FFFFFF);
    render();
}

void child_sigusr2(int sig)
{
    usleep(100000);
    _exit(0);
}
