all: shared myxwindow

shared: myshared.c
	gcc myshared.c -Wall -o shared

myxwindow: myxwindow.c
	gcc myxwindow.c -Wall -lX11 -o myxwindow

clean: 
	rm -r shared myxwindow