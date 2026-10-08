// Christian Rodriguez
// Backup phase 4 incase something goes wrong
//
// CMPS-3600 Fall 2025
// program:  bbphase4.c
// author:   Gordon Griesel
// purpose:  Framework for animated graphics
//           Using XWindows (Xlib) for drawing pixels
//           Close-with-click-on-x is implemented <-----
//           (credit: Taylor Hooser Spring 2023)
//           Double buffer used for smooth animation
//           No flickering
// 
// DBE means double buffer extension.
// It's an extersion of X11 that uses a video back-buffer.
// Draw to a back-buffer, then swap to the video memory when ready.
// 
// compile like this:
// 
//     $ gcc phase4_bak.c -Wall -lX11 -lXext -lpthread
// 
// Press 'C' to see collisions of the cars in the intersection.
// Press 'S' to slow the cars in the intersection.
// The position of the collision is marked.
// Stop the collisions using POSIX or SysV semaphores, or POSIX mutex.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/Xdbe.h>
#include <X11/Xatom.h> /* for intercepting X click to close */

#include <sys/wait.h>   /* for wait system call */
#include <signal.h>     /* added: signals */
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/file.h>   /* open() for log file */
#include <fcntl.h>      /* fcntl() for non-blocking pipe */

#define NCARS 8

void init();
void init_xwindows(int, int);
void cleanup_xwindows(void);
void check_resize(XEvent *e);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void physics(void);
void render(void);
//
//---------------------------------
//globals to make your life easier.
struct Global {
	Display *dpy;
	Window win;
	GC gc;
	XdbeBackBuffer backBuffer;
	XdbeSwapInfo swapInfo;
	Atom wm_delete_window; /* credit: Taylor Hooser */
	int xres, yres;
	int collision_flag;
	int collision[NCARS];
	int crash[2];
	int show_collisions;
	int ncollisions;
	int slow_mode;

	pthread_mutex_t intersection_mutex; // mutex for intersection
	int passes[NCARS];

	int child_pos[2];
	int parent_pos[2];
	int parent_dim[2];
	int nchildren;

	int pause;
} g;

struct Box {
	double pos[2];
	double vel[2];
	int w, h;
} intersection, cars[NCARS];

// STATS CODE

/* forward decls for child signal handlers and xeyes launcher */

int child = 0;    // <- to know if window = child
int childActive;  // <- flag to know if CHILD is Active
pid_t child_pid = -1;         /* pid of our child window */

void make_child_window();
void make_stats();
void stats_render();
int stats_keys(XEvent *e);
void get_stats();

void moveWindow(int x, int y);
void myhandler(int sig);

char **myargv;
char **myenvp;


// STATS IPC -------------------
struct StatsMsg {
    long type;
    int  collisions;
    int  passes[NCARS];
} mymsg;

int mqid  = -1;   // message queue id
int shmid = -1;   // shared memory id
int *shared = (void *)-1;   // shared memory pointer
int logfd  = -1;  // log file descriptor
// -----------------------------


// Moving child window -------------------
typedef struct {
    int x;
    int y;
} WindowPositionMessage;

// Parent writes new positions into this pipe,
// child reads them and moves its window.
int parent_to_child_pipe_read_fd  = -1; // child uses this end
int parent_to_child_pipe_write_fd = -1; // parent uses this end

void poll_for_parent_move(void);
// ---------------------------------------

// END OF STATS CODE

int main(int argc, char *argv[], char *envp[])
{
    myargv = argv;
    myenvp = envp;

    // --- Detect if this process is the child or the parent ---
    // Parent runs as:   ./bbphase4
    // Child runs as:    ./bbphase4 xxx-child-xxx <mqid> <pipe_read_fd> <pipe_write_fd>
    if (argc > 1 && strcmp(argv[1], "xxx-child-xxx") == 0) {
        // Child process after execve
        child = 1;

        if (argc < 5) {
            fprintf(stderr,
                    "Usage (child): %s xxx-child-xxx <mqid> <pipe_read_fd> <pipe_write_fd>\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }

        //  argv[2] -> message queue id (from parent)
        //  argv[3] -> read end of parent->child pipe
        //  argv[4] -> write end of parent->child pipe (child will close it)
        mqid  = atoi(argv[2]);
        parent_to_child_pipe_read_fd  = atoi(argv[3]);
        parent_to_child_pipe_write_fd = atoi(argv[4]);

        // Child only needs the read end; close write end.
        close(parent_to_child_pipe_write_fd);
        parent_to_child_pipe_write_fd = -1;

        // Make the read end non-blocking so child does NOT freeze
        // while waiting for parent movement messages.
        int flags = fcntl(parent_to_child_pipe_read_fd, F_GETFL, 0);
        fcntl(parent_to_child_pipe_read_fd, F_SETFL, flags | O_NONBLOCK);

    } else {
        // Parent process
        child = 0;
    }

    if (!child) {
		// --- Signals ---
		// Parent watches for child exit
		signal(SIGCHLD, myhandler);
				
		// --- IPC SETUP (parent only) ---
		char pathname[200];
        getcwd(pathname, 200);
        strcat(pathname, "/foo");

        int ipckey = ftok(pathname, 25);
        if (ipckey == -1) {
            perror("ipckey error");
            exit(EXIT_FAILURE);
        }

        // Shared memory: store simple summary (like total collisions)
        shmid = shmget(ipckey, sizeof(int) * 2, IPC_CREAT | 0666);
        if (shmid < 0) {
            perror("shmget");
            exit(EXIT_FAILURE);
        }
        shared = shmat(shmid, (void *)0, 0);
        if (shared == (void *)-1) {
            perror("shmat");
            exit(EXIT_FAILURE);
        }
        shared[0] = 0;

        // Message queue for full stats
        mqid = msgget(ipckey, IPC_CREAT | 0666);
        if (mqid < 0) {
            perror("msgget");
            exit(EXIT_FAILURE);
        }

        // Open log file
        logfd = open("log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (logfd < 0) {
            perror("open log");
            // not fatal for the simulation
        }
    
		// --- Main behaviour: parent = simulation, child = stats window ---

        init_xwindows(460, 460);
        init();

        pthread_t tid[NCARS];
        void *traffic(void *arg);
        int i;
        for (i = 0; i < NCARS; i++)
            pthread_create(&tid[i], NULL, traffic, (void *)(long)i);

        int done = 0;
        while (!done) {
            while (XPending(g.dpy)) {
                XEvent e;
                XNextEvent(g.dpy, &e);
                check_resize(&e);
                check_mouse(&e);
                done = check_keys(&e);
            }
            if (!g.pause)
                physics();
            render();
            XdbeSwapBuffers(g.dpy, &g.swapInfo, 1);
            usleep(4000);
        }

        // Parent IPC cleanup
        if (shared != (void *)-1)
            shmdt(shared);
        if (shmid >= 0)
            shmctl(shmid, IPC_RMID, 0);
        if (mqid >= 0)
            msgctl(mqid, IPC_RMID, NULL);
        if (logfd >= 0)
            close(logfd);

    } else {
        // Child: only shows stats, using mqid and pipe passed on command line
        make_stats();

        // Child does NOT remove IPC objects, it only detaches.
        if (shared != (void *)-1)
            shmdt(shared);
        if (logfd >= 0)
            close(logfd);
    }

    cleanup_xwindows();
    return 0;
}


int fib(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return fib(n-1) + fib(n-2);
}

int overlap(struct Box *c, struct Box *i)
{
	//This is classic collision detection of rectangles.
	//Does one rectangle overlap another rectangle?
	if (c->pos[0] + (c->w >> 1) < i->pos[0] - (i->w >> 1)) return 0;
	if (c->pos[0] - (c->w >> 1) > i->pos[0] + (i->w >> 1)) return 0;
	if (c->pos[1] + (c->h >> 1) < i->pos[1] - (i->h >> 1)) return 0;
	if (c->pos[1] - (c->h >> 1) > i->pos[1] + (i->h >> 1)) return 0;
	return 1;
}

void *traffic(void *arg)
{
	//This is a thread.
	//Each car will run this thread.
	int carnum = (int)(long)arg;
	//This thread will run forever.
	//Calls to fib() are used to make threads run at different speeds.
	while (1) {
		fib(rand() % 5 + 2);
		//move the car...
		if (!g.pause) {
			cars[carnum].pos[0] += cars[carnum].vel[0]; 
			cars[carnum].pos[1] += cars[carnum].vel[1];
		}
		//Is car in the intersection???
		if (overlap(&cars[carnum], &intersection)) {
			//Car is in the intersection.
			pthread_mutex_lock(&g.intersection_mutex); // NEW: claim the intersection

			/* Critical section */
			while (overlap(&cars[carnum], &intersection)) {
				//Loop here until out of the intersection.
				fib(rand() % 5 + 2);
				if (g.slow_mode)
					fib(15);
				//move the car...
				if (!g.pause) {
					cars[carnum].pos[0] += cars[carnum].vel[0]; 
					cars[carnum].pos[1] += cars[carnum].vel[1];
				}
			}
			g.passes[carnum]++;
			pthread_mutex_unlock(&g.intersection_mutex); // NEW: release the intersection

			/* End critical section */
		}
		//Check for this car outside of the window.
		//If outside, car will enter from other side of window.
		//Classic continuous animation loop.
		//left
		if (cars[carnum].pos[0] < -20 && cars[carnum].vel[0] < 0.0) {
			cars[carnum].pos[0] += g.xres + 40.0;
			cars[carnum].vel[0] = -(rand() % 3 + 1);
			cars[carnum].vel[0] *= 0.0002;
		}
		//top
		if (cars[carnum].pos[1] < -20 && cars[carnum].vel[1] < 0.0) {
			cars[carnum].pos[1] += g.yres + 40.0;
			cars[carnum].vel[1] = -(rand() % 3 + 1);
			cars[carnum].vel[1] *= 0.0002;
		}
		//right
		if (cars[carnum].pos[0] > g.xres + 20 && cars[carnum].vel[0] > 0.0) {
			cars[carnum].pos[0] -= (g.xres + 40.0);
			cars[carnum].vel[0] = (rand() % 3 + 1);
			cars[carnum].vel[0] *= 0.0002;
		}
		//bottom
		if (cars[carnum].pos[1] > g.yres + 20 && cars[carnum].vel[1] > 0.0) {
			cars[carnum].pos[1] -= (g.yres + 40.0);
			cars[carnum].vel[1] = (rand() % 3 + 1);
			cars[carnum].vel[1] *= 0.0002;
		}
	}
	return (void *)0;
}

void cleanup_xwindows(void)
{
	//Deallocate back buffer
	if(!XdbeDeallocateBackBufferName(g.dpy, g.backBuffer)) {
		fprintf(stderr,"Error : unable to deallocate back buffer.\n");
	}
	XFreeGC(g.dpy, g.gc);
	XDestroyWindow(g.dpy, g.win);
	XCloseDisplay(g.dpy);

}

void set_window_title()
{
	char ts[256];
	sprintf(ts, "3600 Intersection %ix%i", g.xres, g.yres);
	if (child)
		sprintf(ts, "stats %ix%i", g.xres, g.yres);
	XStoreName(g.dpy, g.win, ts);
}

void init_xwindows(int w, int h)
{
	g.xres = w;
	g.yres = h;
	XSetWindowAttributes attributes;
	//int screen;
	int major, minor;
	XdbeBackBufferAttributes *backAttr;
	//XGCValues gcv;
	g.dpy = XOpenDisplay(NULL);
    //Use default screen
	//screen = DefaultScreen(dpy);
    //List of events we want to handle
	attributes.event_mask = ExposureMask | StructureNotifyMask |
							PointerMotionMask | ButtonPressMask |
							ButtonReleaseMask | KeyPressMask | KeyReleaseMask;
	//Various window attributes
	attributes.backing_store = Always;
	attributes.save_under = True;
	attributes.override_redirect = False;
	attributes.background_pixel = 0x00000000;
	//Get default root window
	Window root;
	root = DefaultRootWindow(g.dpy);
	//Create a window
	g.win = XCreateWindow(g.dpy, root, 0, 0, g.xres, g.yres, 0,
					    CopyFromParent, InputOutput, CopyFromParent,
					    CWBackingStore | CWOverrideRedirect | CWEventMask |
						CWSaveUnder | CWBackPixel, &attributes);
	//Create gc
	g.gc = XCreateGC(g.dpy, g.win, 0, NULL);
	//Get DBE version
	if (!XdbeQueryExtension(g.dpy, &major, &minor)) {
		fprintf(stderr, "Error : unable to fetch Xdbe Version.\n");
		XFreeGC(g.dpy, g.gc);
		XDestroyWindow(g.dpy, g.win);
		XCloseDisplay(g.dpy);
		exit(1);
	}
	printf("Xdbe version %d.%d\n", major, minor);
	//Get back buffer and attributes (used for swapping)
	g.backBuffer = XdbeAllocateBackBufferName(g.dpy, g.win, XdbeUndefined);
	backAttr = XdbeGetBackBufferAttributes(g.dpy, g.backBuffer);
    g.swapInfo.swap_window = backAttr->window;
    g.swapInfo.swap_action = XdbeUndefined;
	XFree(backAttr);
	//Map and raise window
	set_window_title();
	XMapWindow(g.dpy, g.win);
	XRaiseWindow(g.dpy, g.win);
	//
	//To intercept user clicking x in title bar.
    g.wm_delete_window = XInternAtom(g.dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(g.dpy, g.win, &g.wm_delete_window, 1);
}

void fillRectangle(int x, int y, int w, int h)
{
	XFillRectangle(g.dpy, g.backBuffer, g.gc, x, y, w, h);
}

void drawRectangle(int x, int y, int w, int h)
{
	XDrawRectangle(g.dpy, g.backBuffer, g.gc, x, y, w, h);
}

void drawLine(int x0, int y0, int x1, int y1)
{
	XDrawLine(g.dpy, g.backBuffer, g.gc, x0, y0, x1, y1);
}

void drawString(int x, int y, char *str)
{
	XDrawString(g.dpy, g.backBuffer, g.gc, x, y, str, strlen(str));
}

void init(void)
{
	//Initialize cars direction, speed, etc.
	srand((unsigned)time(NULL));
	g.collision_flag = 0;
	g.show_collisions = 0;
	g.ncollisions = 0;
	g.slow_mode = 0;

	g.pause = 0;
	//the intersection
	intersection.w = 112;
	intersection.h = 112;
	intersection.pos[0] = g.xres / 2;
	intersection.pos[1] = g.yres / 2;
	intersection.vel[0] = 0;
	intersection.vel[1] = 0;
	//
	//cars...
	//
	//         1
	//         |
	//         v
	//       +-----+
	//       |     | <--2
	//  0--> |     |
	//       +-----+
	//           ^
	//           |
	//           3
	//
	int i;
	//initial size and position of each car
	for (i=0; i<NCARS; i++) {
		cars[i].w = 18;
		cars[i].h = 18;
		cars[i].pos[0] = intersection.pos[0];
		cars[i].pos[1] = intersection.pos[1];
		cars[i].vel[0] = 0;
		cars[i].vel[1] = 0;
	}
	int offset = 21;
	offset = 15;

	// NOTES: if you are going south and north, decrease width(thinner car), increase height(longer car)
	// NOTES: if you are going east and west, decrease height(wider car), increase width (longer car)

	//Car heading West
	i = 0;
	
	cars[i].w -= rand() % 4 + 1;
	cars[i].h += rand() % 4 + 14;
	cars[i].pos[0] = g.xres + 30;
	cars[i].pos[1] -= offset;
	cars[i].vel[0] = -(rand() % 3 + 1);
	cars[i].vel[1] = 0;
	//Car heading East
	i = 1;
	cars[i].w += rand() % 4 + 14;
	cars[i].pos[0] = -40;
	cars[i].pos[1] += offset;
	cars[i].vel[0] = rand() % 3 + 1;
	cars[i].vel[1] = 0;
	//Car heading South
	i = 2;
	cars[i].w -= rand() % 4 + 2;
	cars[i].h += rand() % 4 + 14;
	cars[i].pos[0] -= offset;
	cars[i].pos[1] = -30;
	cars[i].vel[0] = 0;
	cars[i].vel[1] = rand() % 3 + 1;
	//Car heading North
	i = 3;
	cars[i].w += rand() % 4 + 10;
	cars[i].h += rand() % 4 + 60;
	cars[i].pos[0] += offset;
	cars[i].pos[1] = g.yres + 30;
	cars[i].vel[0] = 0;
	cars[i].vel[1] = -(rand() % 3 + 1);
	//
	//Another car heading West
	i = 4;
	cars[i].w += rand() % 4 + 14;
	cars[i].pos[0] = g.xres + 30;
	cars[i].pos[1] -= (offset * 3);
	cars[i].vel[0] = -(rand() % 3 + 1);
	cars[i].vel[1] = 0;
	//Car heading East
	i = 5;
	cars[i].h -= rand() % 4 + 5;
	cars[i].w += rand() % 4 + 20;
	cars[i].pos[0] = -40;
	cars[i].pos[1] += (offset * 3);
	cars[i].vel[0] = rand() % 3 + 1;
	cars[i].vel[1] = 0;
	//Car heading South
	i = 6;
	cars[i].h += rand() % 4 + 14;
	cars[i].pos[0] -= (offset * 3);
	cars[i].pos[1] = -30;
	cars[i].vel[0] = 0;
	cars[i].vel[1] = rand() % 3 + 1;
	//Car heading North
	i = 7;
	cars[i].h += rand() % 4 + 54;
	cars[i].pos[0] += (offset * 3);
	cars[i].pos[1] = g.yres + 30;
	cars[i].vel[0] = 0;
	cars[i].vel[1] = -(rand() % 3 + 1);
	//Scale the velocity...
	for (i=0; i<NCARS; i++) {
		cars[i].vel[0] *= 0.0002;
		cars[i].vel[1] *= 0.0002;
	}
}

void check_resize(XEvent *e)
{
    //ConfigureNotify is sent when the window is resized or moved.
    if (e->type != ConfigureNotify)
        return;
    XConfigureEvent xce = e->xconfigure;
    g.xres = xce.width;
    g.yres = xce.height;
    if (child) {
        //store the child's position
        g.child_pos[0] = xce.x;
        g.child_pos[1] = xce.y;
    }
    if (!child) {
        Window root = DefaultRootWindow(g.dpy);
        Window chld;
        int x, y;
        XTranslateCoordinates(g.dpy, g.win, root, 0, 0, &x, &y, &chld);
        g.parent_pos[0] = x;
        g.parent_pos[1] = y;
        g.parent_dim[0] = xce.width;
        g.parent_dim[1] = xce.height;
        //parent sends its new position to the child.
        // if (g.nchildren > 0) {
        // }

		// If stats window (child) is active, send it a new desired position.
        if (childActive && parent_to_child_pipe_write_fd >= 0) {
            WindowPositionMessage msg;
            // Put child window just to the right of the parent
            msg.x = g.parent_pos[0] + g.parent_dim[0] + 10; // 10 px gap
            msg.y = g.parent_pos[1];

            write(parent_to_child_pipe_write_fd, &msg, sizeof(msg));
        }
    }
    set_window_title();
    usleep(4000);
}

void moveWindow(int x, int y)
{
    XMoveWindow(g.dpy, g.win, x, y);
}

void clear_screen(void)
{
	//XClearWindow(dpy, win);
	XSetForeground(g.dpy, g.gc, 0x00050505);
	XFillRectangle(g.dpy, g.backBuffer, g.gc, 0, 0, g.xres, g.yres);
}

void check_mouse(XEvent *e)
{
	static int savex = 0;
	static int savey = 0;

    if (e->type != ButtonPress && e->type != ButtonRelease &&
										e->type != MotionNotify) {
        return;
	}
	if (e->type == ButtonRelease)
		return;
	if (e->type == ButtonPress) {
		//Log("ButtonPress %i %i\n", e->xbutton.x, e->xbutton.y);
		if (e->xbutton.button==1) { }
		if (e->xbutton.button==3) { }
	}
	if (e->type == MotionNotify) {
		if (savex != e->xbutton.x || savey != e->xbutton.y) {
			//mouse moved
			savex = e->xbutton.x;
			savey = e->xbutton.y;
			write(1, child ? "c" :"p", 1);

		}
	}
}

int check_keys(XEvent *e)
{
    //======================================================
    //To intercept user clicking X in title bar to close.
	//Not a keyboard event, but placed here for convenience.
	if (e->type == ClientMessage) {
		// if x button clicked, DO NOT CLOSE WINDOW
		// instead, overwrite default handler
	    if ((Atom)e->xclient.data.l[0] == g.wm_delete_window)
    	    return 1;
	}
    //======================================================
	//
	if (e->type != KeyPress && e->type != KeyRelease)
		return 0;
	int key = XLookupKeysym(&e->xkey, 0);
	if (e->type == KeyPress) {
		switch (key) {
			case XK_c:
				g.show_collisions ^= 1;
				break;
			case XK_s:
				g.slow_mode ^= 1;
				break;
			case XK_p:
			case XK_P:
				g.pause ^= 1;
				break;
			case XK_w:
			case XK_W:
				if (!childActive)
                    make_child_window();
				break;
			case XK_Escape:
				return 1;
		}
	}
	return 0;
}

void physics()
{
	//check for car collisions...
	g.collision_flag = 0;
	int i, j;
	for (i=0; i<NCARS; i++) {
		for (j=0; j<NCARS; j++) {
			if (i == j)
				continue;
			if (overlap(&cars[i], &cars[j])) {
				g.collision_flag = 1;
				g.collision[0] = cars[i].pos[0];
				g.collision[1] = cars[i].pos[1];
				g.collision[2] = cars[j].pos[0];
				g.collision[3] = cars[j].pos[1];
				g.crash[0] = i;
				g.crash[1] = j;
				++g.ncollisions;
			}
		}
	}

	// STATS IPC: parent writes latest stats to shared memory and queue
    if (!child && mqid >= 0) {
        // shared memory example, simple summary
        shared[0] = g.ncollisions;
        
        // message queue with full per-car stats
        mymsg.type = 1;
        mymsg.collisions = g.ncollisions;
        for (i = 0; i < NCARS; i++)
            mymsg.passes[i] = g.passes[i];
        msgsnd(mqid, &mymsg, sizeof(mymsg) - sizeof(long), IPC_NOWAIT);
    }
}

void render(void)
{
	clear_screen();
	XSetForeground(g.dpy, g.gc, 0x00ff0000);
	//draw intersection
	//XSetForeground(g.dpy, g.gc, 0x00ffff55);
	XSetForeground(g.dpy, g.gc, 0x00aaaa55);
	drawRectangle(intersection.pos[0] - (intersection.w >> 1),
					intersection.pos[1] - (intersection.h >> 1),
					intersection.w, intersection.h);
	//roadway color
	XSetForeground(g.dpy, g.gc, 0x00333333);
	//roadway north
	fillRectangle(	intersection.pos[0] - (intersection.w >> 1),
					0,
					intersection.w,
					(g.yres >> 1) - (intersection.h >> 1) - 1);
	//roadway south
	fillRectangle(	intersection.pos[0] - (intersection.w >> 1),
					(g.yres>>1) + (intersection.h >> 1) + 2,
					intersection.w,
					(g.yres >> 1) - (intersection.h >> 1));
	//roadway east
	fillRectangle(	0,
					(g.yres>>1) - (intersection.h >> 1),
					(g.xres >> 1) - (intersection.w >> 1) - 1,
					intersection.h);
	//roadway west
	fillRectangle(	(g.xres >> 1) + (intersection.w >> 1) + 2,
					(g.yres>>1) - (intersection.h >> 1),
					(g.xres >> 1) - (intersection.w >> 1) - 1,
					intersection.h);
	//Highway dashed lines
	XSetForeground(g.dpy, g.gc, 0x00666655);
	//dashed lines north
	int i;
	int y1 = 0;
	int y2 = 20;
	for (i=0; i<5; i++) {
		fillRectangle(intersection.pos[0] - 2, y1, 4, y2);
		y1 += y2 + 9;
	}
	//dashed lines south
	y1 = 20;
	y2 = 20;
	for (i=0; i<5; i++) {
		fillRectangle(intersection.pos[0] - 2, g.yres - 1 - y1, 4, y2);
		y1 += 29;
	}
	//dashed lines west
	int x1 = 0;
	int x2 = 20;
	for (i=0; i<5; i++) {
		fillRectangle(x1, intersection.pos[1] - 2, x2, 4);
		x1 += x2 + 9;
	}
	//dashed lines east
	x1 = 20;
	x2 = 20;
	for (i=0; i<5; i++) {
		fillRectangle(g.xres - 1 - x1, intersection.pos[1] - 2, x2, 4);
		x1 += 29;
	}

	//draw cars
	unsigned int col[] = {
		0x00ff0000, 0x0000ff00, 0x004444ff, 0x00ff00ff, 0x00ffcc88};
	//int i;
	for (i=0; i<NCARS; i++) {
		XSetForeground(g.dpy, g.gc, col[i%5]);
		fillRectangle(cars[i].pos[0] - (cars[i].w >> 1),
						cars[i].pos[1] - (cars[i].h >> 1),
						cars[i].w, cars[i].h);
	}
	//Key options...
	int y = 20;
	char str[100];
	sprintf(str, "'C' = see collisions");
	XSetForeground(g.dpy, g.gc, 0x0000ff00);
	drawString(20, y, str);
	y += 16;
	sprintf(str, (!g.slow_mode) ? "'S' = slow mode" : "'S' = stop slow mode");
	XSetForeground(g.dpy, g.gc, 0x0000ff00);
	drawString(20, y, str);
	y += 16;
	sprintf(str, (!g.pause) ? "'P' = pause" : "'P' = unpause");
	XSetForeground(g.dpy, g.gc, 0x0000ff00);
	drawString(20, y, str);
	y += 16;
	sprintf(str, "'W' = show stats");
	XSetForeground(g.dpy, g.gc, 0x0000ff00);
	drawString(20, y, str);
	y += 16;
	sprintf(str, " n collisions: %i", g.ncollisions);
	XSetForeground(g.dpy, g.gc, 0x00ffff00);
	drawString(20, y, str);
	//passes per car
	for (i=0; i<NCARS; i++) {
		char temp[32];
		sprintf(temp, " car %i passes: %i", i, g.passes[i]);
		strcat(str, temp);
		y += 16;
		drawString(300, (i+1)*16, temp);
	}
	if (g.show_collisions) {
		if (g.collision_flag) {
			//show collision with lines drawn fron corner.
			XSetForeground(g.dpy, g.gc, col[g.crash[0]]);
			drawLine(g.xres-1, 0, g.collision[0], g.collision[1]);
			XSetForeground(g.dpy, g.gc, col[g.crash[1]]);
			drawLine(g.xres-1, 0, g.collision[2], g.collision[3]);
		}
	}
}

// Stats

void make_child_window()
{
    childActive = 0;

    int fds[2];
    if (pipe(fds) == -1) {
        perror("pipe");
        return;
    }

    // Save pipe ends in globals so parent and child can refer to them.
    parent_to_child_pipe_read_fd  = fds[0];
    parent_to_child_pipe_write_fd = fds[1];

    pid_t pid = fork();
    if (pid == 0) {
        // --- CHILD (before exec) ---

        // Build strings for command-line arguments.
        char mqid_str[16];
        char read_fd_str[16];
        char write_fd_str[16];

        snprintf(mqid_str,     sizeof(mqid_str),     "%d", mqid);
        snprintf(read_fd_str,  sizeof(read_fd_str),  "%d", parent_to_child_pipe_read_fd);
        snprintf(write_fd_str, sizeof(write_fd_str), "%d", parent_to_child_pipe_write_fd);

        // Argument list:
        //   argv[0] = program name
        //   argv[1] = "xxx-child-xxx"  (marker so main() knows it's the child)
        //   argv[2] = mqid
        //   argv[3] = pipe read fd
        //   argv[4] = pipe write fd
        char *arg[] = {
            myargv[0],
            "xxx-child-xxx",
            mqid_str,
            read_fd_str,
            write_fd_str,
            NULL
        };

        execve(arg[0], arg, myenvp);
        perror("execve");
        _exit(1);

    } else if (pid > 0) {
        // --- PARENT ---
        // Parent only needs the write end for sending positions.
        close(parent_to_child_pipe_read_fd);
        parent_to_child_pipe_read_fd = -1;

        signal(SIGCHLD, myhandler);
        child_pid = pid;
        childActive = 1;

    } else {
        // fork failed
        perror("fork");
        close(fds[0]);
        close(fds[1]);
    }
}

void make_stats() 
{
    init_xwindows(260, 260);
    init();

    int done = 0;
    while (!done) {
        while (XPending(g.dpy)) {
            XEvent e;
            XNextEvent(g.dpy, &e);
            check_resize(&e);
            check_mouse(&e);
            done = stats_keys(&e);
        }

        // Check if the parent has moved and update our position.
        poll_for_parent_move();

        stats_render();
        XdbeSwapBuffers(g.dpy, &g.swapInfo, 1);
        usleep(4000);
    }
}

void stats_render()
{
	clear_screen();
	XSetForeground(g.dpy, g.gc, 0x0000ff00);

	get_stats();

	int y = 30;
	char str[100];

	sprintf(str, "Traffic statistics");
	drawString(20, y, str);
	y += 20;

	sprintf(str, " n collisions: %i", mymsg.collisions);
	XSetForeground(g.dpy, g.gc, 0x00ffff00);
	drawString(20, y, str);
	y += 20;

	//passes per car
	for (int i=0; i<NCARS; i++) {
		char temp[32];
		sprintf(temp, " car %i passes: %i", i, mymsg.passes[i]);
		drawString(20, y, temp);
		y += 16;
	}
}
int stats_keys(XEvent *e)
{
    //======================================================
    //To intercept user clicking X in title bar to close.
	//Not a keyboard event, but placed here for convenience.
	if (e->type == ClientMessage) {
		// if x button clicked, DO NOT CLOSE WINDOW
		// instead, overwrite default handler
	    if ((Atom)e->xclient.data.l[0] == g.wm_delete_window)
    	    return 1;
	}
    //======================================================
	//
	if (e->type != KeyPress && e->type != KeyRelease)
		return 0;
	int key = XLookupKeysym(&e->xkey, 0);
	if (e->type == KeyPress) {
		switch (key) {
			case XK_Escape:
				return 1;
		}
	}
	return 0;
}

void get_stats()
{
	// Read the latest stats from the message queue (non-blocking).
	// We empty the queue so we always display the most recent message.
	struct StatsMsg rmsg;
	ssize_t received;
	do {
		received = msgrcv(mqid, &rmsg,
		                  sizeof(rmsg) - sizeof(long),
		                  0, IPC_NOWAIT);
		if (received > 0) {
			mymsg = rmsg; // store latest
		}
	} while (received > 0);
}

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
            }
        }
        usleep(100000);
    }
}

void poll_for_parent_move(void)
{
    if (!child)
        return;
    if (parent_to_child_pipe_read_fd < 0)
        return;

    WindowPositionMessage msg;
    ssize_t bytes;

    // Read all pending messages (non-blocking pipe).
    // Only the most recent position matters.
    while ((bytes = read(parent_to_child_pipe_read_fd,
                         &msg, sizeof(msg))) == sizeof(msg)) {
        moveWindow(msg.x, msg.y);
    }
}
