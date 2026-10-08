# Makefile for week-4

all: lab4 myxwindow shared_mem shm_io sigset sigset2 strings

lab4: bblab4.c
	gcc bblab4.c -Wall -olab4

myxwindow: myxwindow.c
	gcc myxwindow.c -Wall -lX11 -o myxwindow

shared_mem: shared_mem.c
	gcc shared_mem.c -Wall -oshared_mem

shm_io: shm_io.c
	gcc shm_io.c -Wall -oshm_io

sigset: sigset.c
	gcc sigset.c -Wall -osigset

sigset2: sigset2.c
	gcc sigset2.c -Wall -osigset2

strings: strings.c
	gcc strings.c -Wall -ostrings

clean:
	rm -f lab4 myxwindow shared_mem shm_io sigset sigset2 strings
